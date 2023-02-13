#include "PatternStore.h"

#include <utility>

PatternStore::PatternStore(std::shared_ptr<WriteOnlyStorage> storage) : patternStorage(std::move(storage)) {
}

void PatternStore::insertExpressionPattern(std::shared_ptr<AssignNode> node) {
    patternStorage->getPatternManager()->insertPattern(node->stmtIndex, node->varName, node->exprNode->str);
}
