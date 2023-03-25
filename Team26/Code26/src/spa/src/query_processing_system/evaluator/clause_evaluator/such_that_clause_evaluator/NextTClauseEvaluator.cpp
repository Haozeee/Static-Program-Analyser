#include "NextTClauseEvaluator.h"

NextTClauseEvaluator::NextTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

IntIntMap NextTClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTCache()->insertItemsIntoCache(itemsToRead);
    return cache->getNextTCache()->getCacheData();
}

IntIntMap NextTClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    cache->getNextTReverseCache()->insertItemsIntoCache(itemsToRead);
    return cache->getNextTReverseCache()->getCacheData();
}

IntIntMap NextTClauseEvaluator::getRelationshipManager() {
    return getRelationshipCache({});
}

IntIntMap NextTClauseEvaluator::getOppositeRelationshipManager() {
    return getOppositeRelationshipCache({});
}

bool NextTClauseEvaluator::isRelationshipEmpty() {
    return cache->getNextTCache()->isEmpty();
}
