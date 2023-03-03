#include "RelationshipExtractor.h"
#include <utility>

RelationshipExtractor::RelationshipExtractor(std::shared_ptr<IRelationshipStore> relationshipStore) {
    this->relationshipStore = std::move(relationshipStore);
}

void RelationshipExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    parentIndexStack.clear();
    currProcedureName = node->procedureName;
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

void RelationshipExtractor::extractCall(std::shared_ptr<CallNode> node) {
    // TODO(zt): For future sprints
}

void RelationshipExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
    extractCondExpr(node->condExprNode);
    parentIndexStack.emplace_back(node->stmtIndex);
    whileStack.push_back(node->stmtIndex); // CFG
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
    ifStack.emplace_back(node->stmtIndex);
    extractStmtList(node->thenStmtListNode);
    ifThenStatementStack = statementStack;
    resetFlow(ifStack.back());
    extractStmtList(node->elseStmtListNode);
    ifElseStatementStack = statementStack;
    statementStack.clear();
    statementStack.insert(statementStack.end(), ifThenStatementStack.begin(), ifThenStatementStack.end());
    statementStack.insert(statementStack.end(), ifElseStatementStack.begin(), ifElseStatementStack.end());
    ifStack.pop_back();
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

