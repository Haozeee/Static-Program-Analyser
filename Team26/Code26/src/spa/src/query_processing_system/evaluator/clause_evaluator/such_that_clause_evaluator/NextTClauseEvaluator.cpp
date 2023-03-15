#include "NextTClauseEvaluator.h"

NextTClauseEvaluator::NextTClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right, true) {}

std::unordered_map<int, std::unordered_set<int>>
NextTClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTCache()->insertItemsIntoCache(itemsToRead);
    return cache->getNextTCache()->getCacheData();
}

std::unordered_map<int, std::unordered_set<int>>
NextTClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTReverseCache()->insertItemsIntoCache(itemsToRead);
    return cache->getNextTReverseCache()->getCacheData();
}

std::unordered_map<int, std::unordered_set<int>> NextTClauseEvaluator::getRelationshipManager() {
    return getRelationshipCache({});
}

std::unordered_map<int, std::unordered_set<int>>
NextTClauseEvaluator::getOppositeRelationshipManager() {
    return getOppositeRelationshipCache({});
}

bool NextTClauseEvaluator::isRelationshipEmpty() {
    return cache->getNextTCache()->isEmpty();
}
