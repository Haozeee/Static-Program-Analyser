#include "EntityExtractor.h"

#include <utility>

EntityExtractor::EntityExtractor(std::shared_ptr<EntityStore> entityStore) : AbstractExtractor() {
    this->entityStore = entityStore;
}

void EntityExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    entityStore->insertProcedure(node);
    AbstractExtractor::extractProcedure(node);
}

void EntityExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    AbstractExtractor::extractStmtList(node);
}

void EntityExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    entityStore->insertStatement(node);
    AbstractExtractor::extractStmt(node);
}

void EntityExtractor::extractRead(std::shared_ptr<ReadNode> node) {
    entityStore->insertReadStatement(node);
}

void EntityExtractor::extractPrint(std::shared_ptr<PrintNode> node) {
    entityStore->insertPrintStatement(node);
}

void EntityExtractor::extractCall(std::shared_ptr<CallNode> node) {
    entityStore->insertCallStatement(node);
}

void EntityExtractor::extractAssign(std::shared_ptr<AssignNode> node) {
}

void EntityExtractor::extractIf() {
}

void EntityExtractor::extractWhile() {
}

void EntityExtractor::extractCondExpr() {
}

void EntityExtractor::extractExpr() {
}



