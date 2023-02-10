#include "AbstractExtractor.h"

AbstractExtractor::AbstractExtractor() {
}

void AbstractExtractor::extractProgram(std::shared_ptr<ProgramNode> node) {
    for (auto& procedure : node->procedureList) {
        extractProcedure(procedure);
    }
}

void AbstractExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    extractStmtList(node->stmtListNode);
}

void AbstractExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    for (auto& stmt : node->stmtList) {
        extractStmt(stmt);
    }
}

void AbstractExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    currentStmtNo = node->stmtIndex;
    node->evaluate(*this);
}

void AbstractExtractor::extractCondExpr(std::shared_ptr<CondExprNode> node) {

}

void AbstractExtractor::extractExpr(std::shared_ptr<ExprNode> node) {

}
