#include "AbstractSyntaxTreeExtractor.h"

void AbstractSyntaxTreeExtractor::extractProgram(std::shared_ptr<ProgramNode> node) {
    for (auto& procedure : node->procedureList) {
        extractProcedure(procedure);
    }
}

void AbstractSyntaxTreeExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    extractStmtList(node->stmtListNode);
}

void AbstractSyntaxTreeExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    for (auto& stmt : node->stmtList) {
        extractStmt(stmt);
    }
}

void AbstractSyntaxTreeExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    currentStmtNo = node->stmtIndex;
    node->evaluate(*this);
}

AbstractSyntaxTreeExtractor::AbstractSyntaxTreeExtractor(std::shared_ptr<WriteOnlyStorage> storage) : storage(storage)
{
}
