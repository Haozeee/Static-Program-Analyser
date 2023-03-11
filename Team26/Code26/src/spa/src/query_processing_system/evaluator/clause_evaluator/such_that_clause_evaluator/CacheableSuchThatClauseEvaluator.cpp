#include "CacheableSuchThatClauseEvaluator.h"

CacheableSuchThatClauseEvaluator::CacheableSuchThatClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

void CacheableSuchThatClauseEvaluator::setStorageLocation(StoragePointer storage_, CachePointer cache_) {
    storage = storage_;
    cache = cache_;
}

void CacheableSuchThatClauseEvaluator::evaluateSynonymValue() {

}
