#include "PatternStore.h"

void PatternStore::insertExpressionPattern(std::string &expr) {
}

PatternStore::PatternStore(std::shared_ptr<WriteOnlyStorage> storage) : patternStorage(storage) {
}
