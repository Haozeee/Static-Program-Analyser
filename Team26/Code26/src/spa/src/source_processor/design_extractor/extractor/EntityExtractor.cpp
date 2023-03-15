#include "EntityExtractor.h"

#include <utility>
#include <string>

EntityExtractor::EntityExtractor(std::shared_ptr<IEntityStore> entityStore, std::shared_ptr<IPatternStore>
        patternStore) : BaseExtractor() {
    this->entityStore = std::move(entityStore);
    this->patternStore = std::move(patternStore);
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

void EntityExtractor::extractProgram(std::shared_ptr<ProgramNode> node) {
    BaseExtractor::extractProgram(node);
    for (int i = 1; i <= currentStmtNo; i++) {
        entityStore->insertStatement(i);  // Store Statement Index
    }
    patternStore->invokePostReverseRelationship();
}

void EntityExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    entityStore->insertProcedure(node);
    BaseExtractor::extractProcedure(node);
}

void EntityExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
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
    patternStore->insertExpressionPattern(node);
    entityStore->insertAssignStatement(node);
    extractExpr(node->exprNode);
}

void EntityExtractor::extractIf(std::shared_ptr<IfNode> node) {
    entityStore->insertIfStatement(node);
    extractCondExpr(node->condExprNode);
    for (auto &variable : exprVariableList) {
        patternStore->insertCondExpressionIfStatement(node->stmtIndex, variable);
    }
    extractStmtList(node->thenStmtListNode);
    extractStmtList(node->elseStmtListNode);
}

void EntityExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
    entityStore->insertWhileStatement(node);
    extractCondExpr(node->condExprNode);
    for (auto &variable : exprVariableList) {
        patternStore->insertCondExpressionWhileStatement(node->stmtIndex, variable);
    }
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
        entityStore->insertVariableName(variable);
    }
}

