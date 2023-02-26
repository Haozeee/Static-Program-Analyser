#include "RelationshipExtractor.h"
#include <utility>

RelationshipExtractor::RelationshipExtractor(std::shared_ptr<IRelationshipStore> relationshipStore,
        std::shared_ptr<ReadStorage> readStorage) : BaseExtractor() {
    this->relationshipStore = std::move(relationshipStore);
    procedureManager = readStorage->getProcedureManager();
}

void RelationshipExtractor::extractProgram(std::shared_ptr<ProgramNode> node) {
    BaseExtractor::extractProgram(node);
    // TODO(zt): handle
}


void RelationshipExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    parentIndexStack.clear();
    currProcedureName = node->procedureName;
    procedureUniqueCallCount.insert({node->procedureName, 0});
    BaseExtractor::extractProcedure(node);
}

void RelationshipExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    followsStack.push_back(std::make_shared<std::vector<int>>());
    BaseExtractor::extractStmtList(node);
    followsStack.pop_back();
}

void RelationshipExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    BaseExtractor::extractStmt(node);
    node->evaluate(*this);

    std::shared_ptr<std::vector<int>> currentFollowsNesting = followsStack.back();
    if (!currentFollowsNesting->empty()) {
        relationshipStore->insertFollowsRelationship(currentFollowsNesting->back(), (node->stmtIndex));
    }
    currentFollowsNesting->push_back(node->stmtIndex);

    if (!parentIndexStack.empty()) {
        relationshipStore->insertParentsRelationship(parentIndexStack.back(), node->stmtIndex);
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
    extractExpr(node->exprNode);
}

void RelationshipExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
    extractCondExpr(node->condExprNode);
    parentIndexStack.emplace_back(node->stmtIndex);
    extractStmtList(node->stmtListNode);
    parentIndexStack.pop_back();
}

void RelationshipExtractor::extractIf(std::shared_ptr<IfNode> node) {
    extractCondExpr(node->condExprNode);
    parentIndexStack.emplace_back(node->stmtIndex);
    extractStmtList(node->thenStmtListNode);
    extractStmtList(node->elseStmtListNode);
    parentIndexStack.pop_back();
}

void RelationshipExtractor::extractExpr(std::shared_ptr<ExprNode> node) {
    clearExprStack();
    BaseExtractor::extractExpr(node);
    insertExprUsesGroup();
}

void RelationshipExtractor::extractCondExpr(std::shared_ptr<CondExprNode> node) {
    clearExprStack();
    BaseExtractor::extractCondExpr(node);
    insertExprUsesGroup();
}

void RelationshipExtractor::extractCall(std::shared_ptr<CallNode> node) {
    if (currProcedureName == node->procedureName) /* Self call*/ {
        // THROW EXCEPTION
    } else if (!procedureManager->contains(node->procedureName)) /* Callee does not exits*/ {
        // THROW EXCEPTION
    }
//        if () /* If this is the first time current procedure called callee */ {
//            procedureUniqueCallCount[currProcedureName]++;
//        }

    // PKB Update
    relationshipStore->insertCallsRelationship(node->stmtIndex, currProcedureName, node->procedureName);

    if (procedureCalledList.find(node->procedureName) == procedureCalledList.end()) {
        procedureCalledList[node->procedureName] = std::make_unique<std::unordered_set<int>>();
    }

    // callee is called by current index and its parent index
    procedureCalledList[node->procedureName]->insert(node->stmtIndex);

    for (auto& parentIndex : parentIndexStack) {
        procedureCalledList[node->procedureName]->insert(parentIndex);
    }
}

void RelationshipExtractor::insertExprUsesGroup() {
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


