#include "PatternStore.h"

#include <utility>

PatternStore::PatternStore(std::shared_ptr<WriteStorage> storage) {
    patternManager = storage->getPatternManager();
}

void PatternStore::insertExpressionPattern(std::shared_ptr<AssignNode> node) {
    patternManager->insertPattern(node->stmtIndex, node->varName, node->exprNode->getRawString());
}
