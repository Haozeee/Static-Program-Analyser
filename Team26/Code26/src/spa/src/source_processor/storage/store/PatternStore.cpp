#include "PatternStore.h"

PatternStore::PatternStore(std::shared_ptr<WriteOnlyStorage> storage) : patternStorage(storage) {
}

void PatternStore::insertExpressionPattern(std::shared_ptr<AssignNode> node) {
    patternStorage->getPatternManager()->insertPattern(node->stmtIndex,node->varName, node->exprNode->str);
}
