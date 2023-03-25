#include "NextTClauseEvaluator.h"

NextTClauseEvaluator::NextTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

StmtStmtMap NextTClauseEvaluator::getRelationshipCache(StmtSet itemsToRead) {
    return Cache::getCacheData(cache->getNextTCache(), itemsToRead);
}

StmtStmtMap NextTClauseEvaluator::getOppositeRelationshipCache(StmtSet itemsToRead) {
    return Cache::getCacheData(cache->getNextTReverseCache(), itemsToRead);
}

StmtStmtMap NextTClauseEvaluator::getRelationshipManager() {
    return Cache::getEntireCacheData(cache->getNextTCache());
}

StmtStmtMap NextTClauseEvaluator::getOppositeRelationshipManager() {
    return Cache::getEntireCacheData(cache->getNextTReverseCache());
}

bool NextTClauseEvaluator::isRelationshipEmpty() {
    return Cache::isCacheEmpty(cache->getNextTCache());
}
