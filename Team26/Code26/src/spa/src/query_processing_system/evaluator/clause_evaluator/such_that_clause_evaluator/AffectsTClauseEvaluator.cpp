#include "AffectsTClauseEvaluator.h"

AffectsTClauseEvaluator::AffectsTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right, true) {}

std::unordered_map<int, std::unordered_set<int>>
AffectsTClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTCache()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsTCacheableGraph()->getCacheData();
}

std::unordered_map<int, std::unordered_set<int>>
AffectsTClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTReverseCache()->insertItemsIntoCache(itemsToRead);
    return cache->getAffectsTReverseCacheableGraph()->getCacheData();
}

std::unordered_map<int, std::unordered_set<int>> AffectsTClauseEvaluator::getRelationshipManager() {
    return getRelationshipCache({});
}

std::unordered_map<int, std::unordered_set<int>>
AffectsTClauseEvaluator::getOppositeRelationshipManager() {
    return getOppositeRelationshipCache({});
}

bool AffectsTClauseEvaluator::isRelationshipEmpty() {
    return cache->getAffectsTCacheableGraph()->isEmpty();
}

bool AffectsTClauseEvaluator::isLeftArgAmbiguous() {
    return false;
}

bool AffectsTClauseEvaluator::isRightArgAmbiguous() {
    return false;
}
