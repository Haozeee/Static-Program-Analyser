#include "RelationshipExtractor.h"
#include <sstream>
#include <iostream>
#include <utility>

RelationshipExtractor::RelationshipExtractor(std::shared_ptr<RelationshipStore> relationshipStore) : AbstractExtractor
() {
    this->relationshipStore = std::move(relationshipStore);
}

void RelationshipExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    parentStack.clear();
    AbstractExtractor::extractProcedure(node);
}

void RelationshipExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    followsStack.push_back(std::make_shared<std::vector<int>>());
    AbstractExtractor::extractStmtList(node);
    followsStack.pop_back();
}

void RelationshipExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    AbstractExtractor::extractStmt(node);

    std::shared_ptr<std::vector<int>> currentFollowsNesting = followsStack.back();
    if (!currentFollowsNesting->empty()) {
        relationshipStore->insertFollowsRelationship(currentFollowsNesting->back(), currentStmtNo);
    }
    currentFollowsNesting->push_back(currentStmtNo);

    if (!parentStack.empty()) {
        relationshipStore->insertParentsRelationship(parentStack.back(), currentStmtNo);
    }
}

void RelationshipExtractor::extractRead(std::shared_ptr<ReadNode> node) {
}

void RelationshipExtractor::extractPrint(std::shared_ptr<PrintNode> node) {
}

void RelationshipExtractor::extractAssign(std::shared_ptr<AssignNode> node) {
}

void RelationshipExtractor::extractCall(std::shared_ptr<CallNode> node) {
}

void RelationshipExtractor::extractIf() {
}

void RelationshipExtractor::extractWhile() {
}

void RelationshipExtractor::extractCondExpr() {
}

void RelationshipExtractor::extractExpr() {
}
