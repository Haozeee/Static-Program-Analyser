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
    entityStore->insertStatement(node);  // Store Statement Index
    AbstractExtractor::extractStmt(node);  // Update Extractor Current Index
    node->evaluate(*this);
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
    entityStore->insertAssignStatement(node);
    extractExpr(node->exprNode);
}

void EntityExtractor::extractIf(std::shared_ptr<IfNode> node) {
    entityStore->insertIfStatement(node);
    extractCondExpr(node->condExprNode);
    extractStmtList(node->thenStmtListNode);
    extractStmtList(node->elseStmtListNode);
}

void EntityExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
    entityStore->insertWhileStatement(node);
    extractCondExpr(node->condExprNode);
    extractStmtList(node->stmtListNode);
}

