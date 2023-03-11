#include "CacheableSuchThatClauseEvaluator.h"

CacheableSuchThatClauseEvaluator::CacheableSuchThatClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, int>(left, right) {}

void CacheableSuchThatClauseEvaluator::setStorageLocation(StoragePointer storage_, CachePointer cache_) {
    storage = storage_;
    cache = cache_;
}
