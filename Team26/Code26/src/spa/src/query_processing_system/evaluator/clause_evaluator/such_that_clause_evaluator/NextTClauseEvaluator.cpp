#include "NextTClauseEvaluator.h"

NextTClauseEvaluator::NextTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

IntIntMap NextTClauseEvaluator::getRelationshipCache(IntSet itemsToRead) {
    return Cache::getCacheData(cache->getNextTCache(), itemsToRead);
}

IntIntMap NextTClauseEvaluator::getOppositeRelationshipCache(IntSet itemsToRead) {
    return Cache::getCacheData(cache->getNextTReverseCache(), itemsToRead);
}

IntIntMap NextTClauseEvaluator::getRelationshipManager() {
    return Cache::getEntireCacheData(cache->getNextTCache());
}

IntIntMap NextTClauseEvaluator::getOppositeRelationshipManager() {
    return Cache::getEntireCacheData(cache->getNextTReverseCache());
}

bool NextTClauseEvaluator::isRelationshipEmpty() {
    return Cache::isCacheEmpty(cache->getNextTCache());
}
