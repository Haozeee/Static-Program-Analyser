#include "BaseExtractor.h"

BaseExtractor::BaseExtractor() = default;

void BaseExtractor::extractProgram(std::shared_ptr<ProgramNode> node) {
    for (auto& procedure : node->procedureList) {
        extractProcedure(procedure);
    }
}

void BaseExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    extractStmtList(node->stmtListNode);
}

void BaseExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    for (auto& stmt : node->stmtList) {
        extractStmt(stmt);
    }
}

void BaseExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    currentStmtNo = node->stmtIndex;
}

void BaseExtractor::extractCondExpr(std::shared_ptr<CondExprNode> node) {
}

void BaseExtractor::extractExpr(std::shared_ptr<ExprNode> node) {
}
