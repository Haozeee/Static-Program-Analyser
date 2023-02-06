#include "RelationshipExtractor.h"
#include <sstream>
#include <iostream>

RelationshipExtractor::RelationshipExtractor(std::shared_ptr<WriteOnlyStorage> storage) : AbstractSyntaxTreeExtractor(
        storage) {
}

void RelationshipExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    AbstractSyntaxTreeExtractor::extractProcedure(node);
}

void RelationshipExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    AbstractSyntaxTreeExtractor::extractStmtList(node);
}

void RelationshipExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    AbstractSyntaxTreeExtractor::extractStmt(node);

    if (!simpleFollow->empty()) {
//      std::cerr << "PAIR: " << simpleFollow->back() << " and  " << currentStmtNo << std::endl;
        storage->getFollowsManager()->insertRelationship(simpleFollow->back(), currentStmtNo);
    }
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
