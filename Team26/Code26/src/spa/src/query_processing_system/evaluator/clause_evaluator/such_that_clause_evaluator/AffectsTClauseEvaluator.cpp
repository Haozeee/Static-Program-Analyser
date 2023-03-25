#include "AffectsTClauseEvaluator.h"

AffectsTClauseEvaluator::AffectsTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

IntIntMap AffectsTClauseEvaluator::getRelationshipCache(std::unordered_set<int> itemsToRead) {
    return Cache::getCacheData(cache->getAffectsTCache(), itemsToRead);
}

IntIntMap AffectsTClauseEvaluator::getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) {
    return Cache::getCacheData(cache->getAffectsTReverseCache(), itemsToRead);
}

IntIntMap AffectsTClauseEvaluator::getRelationshipManager() {
    return Cache::getEntireCacheData(cache->getAffectsTCache());
}

IntIntMap AffectsTClauseEvaluator::getOppositeRelationshipManager() {
    return Cache::getEntireCacheData(cache->getAffectsTReverseCache());
}

bool AffectsTClauseEvaluator::isRelationshipEmpty() {
    return Cache::isCacheEmpty(cache->getAffectsTCache());
}
