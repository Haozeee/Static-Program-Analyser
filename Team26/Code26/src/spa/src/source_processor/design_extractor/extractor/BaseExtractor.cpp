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

void BaseExtractor::extractExpr(std::shared_ptr<ExprNode> node) {
    if (node->isConstant()) {
        exprIntegerList.emplace_back(node->constant.value());
    } else if (node->isVariable()) {
        exprVariableList.emplace_back(node->varName.value());
    } else {
        BaseExtractor::extractExpr(node->returnNodes()->first);
        BaseExtractor::extractExpr(node->returnNodes()->second);
    }
}

void BaseExtractor::extractCondExpr(std::shared_ptr<CondExprNode> node) {
    if (node->isRelExpr()) {
        BaseExtractor::extractExpr(node->returnRelExprNodes()->first);
        BaseExtractor::extractExpr(node->returnRelExprNodes()->second);
    } else if (node->isUnaryCondExpr()) {
        BaseExtractor::extractCondExpr(node->returnNodes()->front());
    } else {
        BaseExtractor::extractCondExpr(node->returnNodes()->at(0));
        BaseExtractor::extractCondExpr(node->returnNodes()->at(1));
    }
}

void BaseExtractor::clearExprStack() {
    exprVariableList.clear();
    exprIntegerList.clear();
}
