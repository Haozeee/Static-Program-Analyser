#include "AffectsClauseEvaluator.h"

AffectsClauseEvaluator::AffectsClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right, true) {}

std::unordered_map<int, std::unordered_set<int>>
AffectsClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getAffectsCacheableGraph()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsCacheableGraph()->getCacheData();
}

std::unordered_map<int, std::unordered_set<int>>
AffectsClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getAffectsReverseCacheableGraph()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsReverseCacheableGraph()->getCacheData();
}

std::unordered_map<int, std::unordered_set<int>> AffectsClauseEvaluator::getRelationshipManager() {
    return getRelationshipCache({});
}

std::unordered_map<int, std::unordered_set<int>>
AffectsClauseEvaluator::getOppositeRelationshipManager() {
    return getOppositeRelationshipCache({});
}

bool AffectsClauseEvaluator::isRelationshipEmpty() {
    return cache->getAffectsTCacheableGraph()->isEmpty();
}
