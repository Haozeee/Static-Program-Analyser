#include "AffectsClauseEvaluator.h"

AffectsClauseEvaluator::AffectsClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right, true) {}

std::unordered_map<int, std::unordered_set<int>>
AffectsClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTCache()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsCacheableGraph()->getCacheData();
}

std::unordered_map<int, std::unordered_set<int>>
AffectsClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTReverseCache()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsTCacheableGraph()->getCacheData();
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

bool AffectsClauseEvaluator::isLeftArgAmbiguous() {
    return false;
}

bool AffectsClauseEvaluator::isRightArgAmbiguous() {
    return false;
}
