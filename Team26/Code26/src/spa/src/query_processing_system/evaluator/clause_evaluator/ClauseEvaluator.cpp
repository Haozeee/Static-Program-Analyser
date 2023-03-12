#include "ClauseEvaluator.h"

void ClauseEvaluator::optimiseResults() {
    if (!clauseResultTable->getColumnsNames().empty() && clauseResultTable->getNumberOfRows() == 0) {
        clauseResultTable->setNoResults();
    }
}

void ClauseEvaluator::setStorageLocation(StoragePointer storage_, CachePointer cache_) {
    storage = storage_;
    cache = cache_;
}
