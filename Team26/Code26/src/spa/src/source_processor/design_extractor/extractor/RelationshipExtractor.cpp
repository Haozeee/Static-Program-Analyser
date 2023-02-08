#include "RelationshipExtractor.h"
#include <sstream>
#include <iostream>
#include <utility>

RelationshipExtractor::RelationshipExtractor(std::shared_ptr<RelationshipStore> relationshipStore) : AbstractExtractor
() {
    this->relationshipStore = std::move(relationshipStore);
}

void RelationshipExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    AbstractExtractor::extractProcedure(node);
}

void RelationshipExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    AbstractExtractor::extractStmtList(node);
}

void RelationshipExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    AbstractExtractor::extractStmt(node);

    if (!simpleFollow->empty()) {
        // std::cerr << "PAIR: " << simpleFollow->back() << " and  " << currentStmtNo << std::endl;
        // storage->getFollowsManager()->insertRelationship(simpleFollow->back(), currentStmtNo);
    //     storage->getFollowsManager()->insertRelationship(simpleFollow->back(), currentStmtNo,
    //                                                      storage->getFollowsTManager());
    // }
    simpleFollow->push_back(currentStmtNo);
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
