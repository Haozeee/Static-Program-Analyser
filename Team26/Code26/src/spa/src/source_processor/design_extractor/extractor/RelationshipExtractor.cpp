#include "RelationshipExtractor.h"
#include <sstream>
#include <iostream>
#include <utility>

RelationshipExtractor::RelationshipExtractor(std::shared_ptr<RelationshipStore> relationshipStore) : BaseExtractor
() {
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
    node->evaluate(*this);

    std::shared_ptr<std::vector<int>> currentFollowsNesting = followsStack.back();
    if (!currentFollowsNesting->empty()) {
        relationshipStore->insertFollowsRelationship(currentFollowsNesting->back(), currentStmtNo);
    }
    currentFollowsNesting->push_back(currentStmtNo);

    if (!parentIndexStack.empty()) {
        relationshipStore->insertParentsRelationship(parentIndexStack.back(), currentStmtNo);
    }
}

void RelationshipExtractor::extractRead(std::shared_ptr<ReadNode> node) {
    relationshipStore->insertModifiesSRelationship(node->stmtIndex, node->varName);
    relationshipStore->insertModifiesPRelationship(currProcedureName, node->varName);
    for (int& parentIndex : parentIndexStack) {
        relationshipStore->insertModifiesSRelationship(parentIndex, node->varName);
    }
}

void RelationshipExtractor::extractPrint(std::shared_ptr<PrintNode> node) {
    relationshipStore->insertUsesSRelationship(node->stmtIndex, node->varName);
    relationshipStore->insertUsesPRelationship(currProcedureName, node->varName);
    for (int& parentIndex : parentIndexStack) {
        relationshipStore->insertUsesSRelationship(parentIndex, node->varName);
    }
}

void RelationshipExtractor::extractAssign(std::shared_ptr<AssignNode> node) {
    relationshipStore->insertModifiesSRelationship(node->stmtIndex, node->varName);
    relationshipStore->insertModifiesPRelationship(currProcedureName, node->varName);
    for (int& parentIndex : parentIndexStack) {
        relationshipStore->insertModifiesSRelationship(parentIndex, node->varName);
    }
}

void RelationshipExtractor::extractCall(std::shared_ptr<CallNode> node) {
}

void RelationshipExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
    extractCondExpr(node->condExprNode);
    parentIndexStack.emplace_back(currentStmtNo);
    extractStmtList(node->stmtListNode);
    parentIndexStack.pop_back();
}

void RelationshipExtractor::extractIf(std::shared_ptr<IfNode> node) {
    extractCondExpr(node->condExprNode);
    parentIndexStack.emplace_back(currentStmtNo);
    extractStmtList(node->thenStmtListNode);
    extractStmtList(node->elseStmtListNode);
    parentIndexStack.pop_back();
}

void RelationshipExtractor::extractCondExpr(std::shared_ptr<CondExprNode> node) {
    clearExprStack();
    BaseExtractor::extractCondExpr(node);
    for (auto &variable : exprVariableList) {
        relationshipStore->insertUsesSRelationship(currentStmtNo, variable);
        for (int& parentIndex : parentIndexStack) {
            relationshipStore->insertUsesSRelationship(parentIndex, variable);
        }
        relationshipStore->insertUsesPRelationship(currProcedureName, variable);
    }
}
