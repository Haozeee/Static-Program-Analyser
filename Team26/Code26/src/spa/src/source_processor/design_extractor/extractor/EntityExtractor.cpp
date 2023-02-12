#include "EntityExtractor.h"

#include <utility>
#include <string>

EntityExtractor::EntityExtractor(std::shared_ptr<EntityStore> entityStore) : BaseExtractor() {
    this->entityStore = std::move(entityStore);
}

/**
 * Call Flow
 *
 * BaseExtractor::extractProgram()
 * EntityExtractor::extractProcedure()
 * BaseExtractor::extractProcedure()
 * BaseExtractor::extractStmtList()
 * EntityExtractor::extractStmt()
 * BaseExtractor::extractStmt()
 * evaluate() base on individual statement implementation
 * */

void EntityExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    entityStore->insertProcedure(node);
    BaseExtractor::extractProcedure(node);
}

void EntityExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    entityStore->insertStatement(node);  // Store Statement Index
    BaseExtractor::extractStmt(node);  // Update Extractor Current Index
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

void EntityExtractor::extractExpr(std::shared_ptr<ExprNode> node) {
    clearExprStack();
    BaseExtractor::extractExpr(node);
    insertExprEntities();
}

void EntityExtractor::extractCondExpr(std::shared_ptr<CondExprNode> node) {
    clearExprStack();
    BaseExtractor::extractCondExpr(node);
    insertExprEntities();
}

void EntityExtractor::insertExprEntities() {
    for (auto &integer : exprIntegerList) {
        entityStore->insertConstant(integer);
    }
    for (auto &variable : exprVariableList) {
        entityStore->insertName(variable);
    }
}

