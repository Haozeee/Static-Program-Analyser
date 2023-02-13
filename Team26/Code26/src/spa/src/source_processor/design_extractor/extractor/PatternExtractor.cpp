#include "PatternExtractor.h"

#include <utility>

PatternExtractor::PatternExtractor(std::shared_ptr<IPatternStore> storage) : BaseExtractor() {
    this->patternStore = std::move(storage);
}

void PatternExtractor::extractAssign(std::shared_ptr<AssignNode> node) {
    patternStore->insertExpressionPattern(node);
}

void PatternExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    if (node->stmtType == StmtType::STMT_ASSIGN) {
         node->evaluatePattern(*this);
    }
}
