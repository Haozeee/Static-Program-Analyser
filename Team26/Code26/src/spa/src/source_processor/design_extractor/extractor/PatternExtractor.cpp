#include "PatternExtractor.h"

#include <utility>

PatternExtractor::PatternExtractor(std::shared_ptr<IPatternStore> storage) : BaseExtractor() {
    this->patternStore = std::move(storage);
}

bool PatternExtractor::isSupported(StmtType type) {
    return type == StmtType::STMT_ASSIGN || type == StmtType::STMT_IF || type == StmtType::STMT_WHILE;
};

void PatternExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    if (isSupported(node->stmtType)) {
         node->evaluatePattern(*this);
    }
}

void PatternExtractor::extractAssign(std::shared_ptr<AssignNode> node) {
    patternStore->insertExpressionPattern(node);
}

void PatternExtractor::extractWhile(std::shared_ptr<WhileNode> node) {
    BaseExtractor::extractStmtList(node->stmtListNode);
}

void PatternExtractor::extractIf(std::shared_ptr<IfNode> node) {
    BaseExtractor::extractStmtList(node->thenStmtListNode);
    BaseExtractor::extractStmtList(node->elseStmtListNode);
}
