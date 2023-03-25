#include "AffectsClauseEvaluator.h"

AffectsClauseEvaluator::AffectsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

IntIntMap AffectsClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getAffectsCacheableGraph()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsCacheableGraph()->getCacheData();
}

IntIntMap AffectsClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getAffectsCacheableGraph()->buildAll();
    return cache->getAffectsCacheableGraph()->getReverseCache();
}

IntIntMap AffectsClauseEvaluator::getRelationshipManager() {
    return getRelationshipCache({});
}

IntIntMap AffectsClauseEvaluator::getOppositeRelationshipManager() {
    return getOppositeRelationshipCache({});
}

bool AffectsClauseEvaluator::isRelationshipEmpty() {
    return cache->getAffectsTCacheableGraph()->isEmpty();
}
