#include "RelationshipExtractor.h"
#include <algorithm>
#include <utility>
#include <queue>

RelationshipExtractor::RelationshipExtractor(std::shared_ptr<IRelationshipStore> relationshipStore) {
    this->relationshipStore = std::move(relationshipStore);
}

void RelationshipExtractor::extractProgram(std::shared_ptr<ProgramNode> node) {
    std::queue<std::string> procedureQueue;
    std::vector<std::string> topologicalSortedProcedures;

    BaseExtractor::extractProgram(node);

    relationshipStore->invokePreReverseRelationship();

    // Interlink ProceduresRelationships
    // Step 1: Toposort Procedures to get DAG (in a vector)
    // procedureUniqueCallCount tracks how many times this procedure calls another procedure uniquely.
    // To form toposort we need start with procedures that are not calling another procedure.
    // There must be at least 1 procedure that is not calling another procedure else cycle

    for (auto& noCallProcedure : procedureUniqueCallCount) {
        if (noCallProcedure.second == 0) {
            procedureQueue.push(noCallProcedure.first);
        }
    }

    callPReversedRelationships = relationshipStore->getCallPReversedRelationship();
    while (!procedureQueue.empty()) {
        currProcedureName = procedureQueue.front();
        procedureQueue.pop();
        topologicalSortedProcedures.emplace_back(currProcedureName);
        // Note: map::operator[] creates empty set and do not throw error, map::at will throw an error

        for (auto &caller : callPReversedRelationships.operator[](currProcedureName)) {
            if (procedureUniqueCallCount.at(caller) > 0) {
                procedureUniqueCallCount.at(caller)--;
            }
            if (procedureUniqueCallCount.at(caller) == 0) {
                procedureQueue.push(caller);
            }
        }
    }

    for (auto &procedureName : topologicalSortedProcedures) {
        interlinkRelationships(procedureName);
    }

    for (auto& procedureName : relationshipStore->getReadProcedureManager()->getAllEntitiesEntries()) {
        if (std::find(topologicalSortedProcedures.begin(), topologicalSortedProcedures.end(), procedureName) ==
        topologicalSortedProcedures.end()) {
            throw SourceExtractorException(RelationshipExtractorCyclicCallsExceptionMessage);
        }
    }

    relationshipStore->invokePostReverseRelationship();
}

void RelationshipExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    parentIndexStack.clear();
    statementStack.clear();
    currProcedureName = node->procedureName;
    if (procedureUniqueCallCount.count(node->procedureName) <= 0) {
        procedureUniqueCallCount.insert({node->procedureName, 0});
    }
    BaseExtractor::extractProcedure(node);
}

void RelationshipExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    followsStack.push_back(std::make_shared<std::vector<int>>());
    BaseExtractor::extractStmtList(node);
    followsStack.pop_back();
}

void RelationshipExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    BaseExtractor::extractStmt(node);

    // CFG
    insertFlow(node->stmtIndex);
    resetFlow(node->stmtIndex);
    node->evaluate(*this);

    std::shared_ptr<std::vector<int>> currentFollowsNesting = followsStack.back();
    if (!currentFollowsNesting->empty()) {
        relationshipStore->insertFollowsRelationship(currentFollowsNesting->back(), (node->stmtIndex));
    }
    for (auto &previousTStmtNo : *currentFollowsNesting) {
        relationshipStore->insertFollowsTRelationship(previousTStmtNo, node->stmtIndex);
    }
    currentFollowsNesting->emplace_back(node->stmtIndex);

    if (!parentIndexStack.empty()) {
        relationshipStore->insertParentsRelationship(parentIndexStack.back(), node->stmtIndex);
    }

    for (auto &previousTStmtNo : parentIndexStack) {
        relationshipStore->insertParentsTRelationship(previousTStmtNo, node->stmtIndex);
    }
}

void RelationshipExtractor::extractRead(std::shared_ptr<ReadNode> node) {
    insertModifiesGroup(node);
}

void RelationshipExtractor::extractPrint(std::shared_ptr<PrintNode> node) {
    insertUsesGroup(node);
}

void RelationshipExtractor::extractAssign(std::shared_ptr<AssignNode> node) {
    insertModifiesGroup(node);
    insertExprUsesGroup(node->exprVariables);
}

void RelationshipExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
    extractCondExpr(node->condExprNode);
    parentIndexStack.emplace_back(node->stmtIndex);
    whileStack.push_back(node->stmtIndex);  // CFG
    extractStmtList(node->stmtListNode);
    parentIndexStack.pop_back();
    // CFG
    insertFlow(whileStack.back());
    resetFlow(whileStack.back());
    whileStack.pop_back();
    // CFG
}

void RelationshipExtractor::extractIf(std::shared_ptr<IfNode> node) {
    extractCondExpr(node->condExprNode);
    parentIndexStack.emplace_back(node->stmtIndex);
    ifStack.emplace_back(node->stmtIndex);  // CFGs
    extractStmtList(node->thenStmtListNode);
    std::vector<int> ifThenStatementStack = statementStack;
    resetFlow(ifStack.back());
    extractStmtList(node->elseStmtListNode);
    std::vector<int> ifElseStatementStack = statementStack;
    statementStack.clear();
    statementStack.insert(statementStack.end(), ifThenStatementStack.begin(), ifThenStatementStack.end());
    statementStack.insert(statementStack.end(), ifElseStatementStack.begin(), ifElseStatementStack.end());
    ifStack.pop_back();
    parentIndexStack.pop_back();
}


void RelationshipExtractor::extractCondExpr(const std::shared_ptr<CondExprNode>& node) {
    insertExprUsesGroup(node->exprVariables);
}

void RelationshipExtractor::extractCall(std::shared_ptr<CallNode> node) {
    if (currProcedureName == node->procedureName) /* Self call*/ {
        throw SourceExtractorException(RelationshipExtractorSelfCallsExceptionMessage);
    } else if (!relationshipStore->getReadProcedureManager()->contains(node->procedureName)) /* Callee does not exits*/ {
        throw SourceExtractorException(RelationshipExtractorNonExistentExceptionMessage);
    }
    if (!relationshipStore->getCallPReadManager()->containsMap(currProcedureName, node->procedureName)) /* Track a procedure's call
 * count */ {
        procedureUniqueCallCount[currProcedureName]++;
    }

    // PKB Insertion
    relationshipStore->insertCallsRelationship(node->stmtIndex, currProcedureName, node->procedureName);

    // Create a unique unordered_set if it does not exist
    if (procedureCalledList.count(node->procedureName) <= 0) {
        procedureCalledList[node->procedureName] = std::make_unique<std::unordered_set<int>>();
    }

    // callee is called by current index and its parent index
    procedureCalledList[node->procedureName]->insert(node->stmtIndex);

    // Uses(p, v) holds if there is a statement s in p or in a procedure called
    // (directly or indirectly) from p such that Uses(s, v) holds.
    for (auto& parentIndex : parentIndexStack) {
        procedureCalledList[node->procedureName]->insert(parentIndex);
    }
}

void RelationshipExtractor::insertExprUsesGroup(const std::unordered_set<std::string>& exprVariableList) {
    for (auto &variable : exprVariableList) {
        relationshipStore->insertUsesSRelationship(currentStmtNo, variable);
        for (int& parentIndex : parentIndexStack) {
            relationshipStore->insertUsesSRelationship(parentIndex, variable);
        }
        relationshipStore->insertUsesPRelationship(currProcedureName, variable);
    }
}

void RelationshipExtractor::insertUsesGroup(const std::shared_ptr<VariableNameNode>& node) {
    relationshipStore->insertUsesSRelationship(node->stmtIndex, node->varName);
    relationshipStore->insertUsesPRelationship(currProcedureName, node->varName);
    for (int& parentIndex : parentIndexStack) {
        relationshipStore->insertUsesSRelationship(parentIndex, node->varName);
    }
}

void RelationshipExtractor::insertModifiesGroup(const std::shared_ptr<VariableNameNode>& node) {
    relationshipStore->insertModifiesSRelationship(node->stmtIndex, node->varName);
    relationshipStore->insertModifiesPRelationship(currProcedureName, node->varName);
    for (int& parentIndex : parentIndexStack) {
        relationshipStore->insertModifiesSRelationship(parentIndex, node->varName);
    }
}

void RelationshipExtractor::insertFlow(int stmtIndex) {
    for (auto& prevStmtIndex : statementStack) {
        relationshipStore->insertNextRelationship(prevStmtIndex, stmtIndex);
    }
}

/**
 * This function clears the statement stacks and sets the stmtIndex as the previous index (first in stack).
 * @param stmtIndex The current index to be tracked as previous index after reset.
 *
 * */
void RelationshipExtractor::resetFlow(int stmtIndex) {
    statementStack.clear();
    statementStack.emplace_back(stmtIndex);
}

void RelationshipExtractor::interlinkSRelationships(const std::string& procedureName) {
    for (auto &variableName : usesPRelationships.operator[](procedureName)) {
        if (procedureCalledList.count(procedureName) > 0) {
            for (auto &statementIndex : *(procedureCalledList.at(procedureName))) {
                relationshipStore->insertUsesSRelationship(statementIndex, variableName);
            }
        }
    }

    for (auto &variableName : modifiesPRelationships.operator[](procedureName)) {
        if (procedureCalledList.count(procedureName) > 0) {
            for (auto &statementIndex : *(procedureCalledList.at(procedureName))) {
                relationshipStore->insertModifiesSRelationship(statementIndex, variableName);
            }
        }
    }
}

void RelationshipExtractor::interlinkPRelationships(const std::string& procedureName) {
    std::unordered_map<std::string, std::unordered_set<std::string>> callsTRelationships
            = relationshipStore->getCallsTRelationship();

    for (auto &caller : callPReversedRelationships.operator[](procedureName)) {
        relationshipStore->insertCallsTRelationship(caller, procedureName);
        for (auto &callee : callsTRelationships.operator[](procedureName)) {
            if (callee == caller) {
                throw SourceExtractorException(RelationshipExtractorSelfCallsExceptionMessage);
            }
            relationshipStore->insertCallsTRelationship(caller, callee);
        }
        for (auto &variableName : usesPRelationships.operator[](procedureName)) {
            relationshipStore->insertUsesPRelationship(caller, variableName);
        }
        for (auto &variableName : modifiesPRelationships.operator[](procedureName)) {
            relationshipStore->insertModifiesPRelationship(caller, variableName);
        }
    }
}

void RelationshipExtractor::interlinkRelationships(const std::string &procedureName) {
    modifiesPRelationships = relationshipStore->getModifiesPRelationship();
    usesPRelationships = relationshipStore->getUsesPRelationship();
    interlinkSRelationships(procedureName);
    interlinkPRelationships(procedureName);
}
