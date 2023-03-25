#include "AffectsTClauseEvaluator.h"

AffectsTClauseEvaluator::AffectsTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

IntIntMap AffectsTClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getAffectsTCacheableGraph()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsTCacheableGraph()->getCacheData();
}

IntIntMap AffectsTClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getAffectsTReverseCacheableGraph()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsTReverseCacheableGraph()->getCacheData();
}

IntIntMap AffectsTClauseEvaluator::getRelationshipManager() {
    return getRelationshipCache({});
}

IntIntMap AffectsTClauseEvaluator::getOppositeRelationshipManager() {
    return getOppositeRelationshipCache({});
}

bool AffectsTClauseEvaluator::isRelationshipEmpty() {
    return cache->getAffectsTCacheableGraph()->isEmpty();
}
