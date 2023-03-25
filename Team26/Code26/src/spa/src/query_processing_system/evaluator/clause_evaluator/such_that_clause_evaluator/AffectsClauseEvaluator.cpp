#include "AffectsClauseEvaluator.h"

AffectsClauseEvaluator::AffectsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

IntIntMap AffectsClauseEvaluator::getRelationshipCache(IntSet itemsToRead) {
    return Cache::getCacheData(cache->getAffectsCache(), itemsToRead);
}

IntIntMap AffectsClauseEvaluator::getOppositeRelationshipCache(IntSet itemsToRead) {
    return cache->getAffectsReverseCacheData();
}

IntIntMap AffectsClauseEvaluator::getRelationshipManager() {
    return Cache::getEntireCacheData(cache->getAffectsCache());
}

IntIntMap AffectsClauseEvaluator::getOppositeRelationshipManager() {
    return cache->getAffectsReverseCacheData();
}

bool AffectsClauseEvaluator::isRelationshipEmpty() {
    return Cache::isCacheEmpty(cache->getAffectsCache());
}
