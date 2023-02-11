#include "EntityExtractor.h"

#include <utility>
#include <string>

EntityExtractor::EntityExtractor(std::shared_ptr<EntityStore> entityStore) : AbstractExtractor() {
    this->entityStore = std::move(entityStore);
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
    entityStore->insertName(node->varName);
}

void EntityExtractor::extractPrint(std::shared_ptr<PrintNode> node) {
    entityStore->insertPrintStatement(node);
    entityStore->insertName(node->varName);
}

void EntityExtractor::extractCall(std::shared_ptr<CallNode> node) {
    entityStore->insertCallStatement(node);
}

void EntityExtractor::extractAssign(std::shared_ptr<AssignNode> node) {
    entityStore->insertName(node->varName);
    entityStore->insertAssignStatement(node);
    // Extract Exception
}

void EntityExtractor::extractIf(std::shared_ptr<IfNode> node) {
    entityStore->insertIfStatement(node);
    extractCondExpr(node->condExprNode);
    extractStmtList(node->thenStmtListNode);
    extractStmtList(node->elseStmtListNode);
}

void EntityExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
}

void EntityExtractor::extractCondExpr(std::shared_ptr<CondExprNode> node) {
}

void EntityExtractor::extractExpr(std::shared_ptr<ExprNode> node) {
}

void EntityExtractor::extractName(std::string name) {
    entityStore->insertName(name);
}

void EntityExtractor::extractInteger(std::string integer) {
    entityStore->insertConstant(integer);
}



