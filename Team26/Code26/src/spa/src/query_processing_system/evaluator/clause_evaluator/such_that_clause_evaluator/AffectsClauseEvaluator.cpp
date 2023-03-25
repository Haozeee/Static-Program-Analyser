#include "AffectsClauseEvaluator.h"

AffectsClauseEvaluator::AffectsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

StmtStmtMap AffectsClauseEvaluator::getRelationshipCache(StmtSet itemsToRead) {
    return Cache::getCacheData(cache->getAffectsCache(), itemsToRead);
}

StmtStmtMap AffectsClauseEvaluator::getOppositeRelationshipCache(StmtSet itemsToRead) {
    return cache->getAffectsReverseCacheData();
}

StmtStmtMap AffectsClauseEvaluator::getRelationshipManager() {
    return Cache::getEntireCacheData(cache->getAffectsCache());
}

StmtStmtMap AffectsClauseEvaluator::getOppositeRelationshipManager() {
    return cache->getAffectsReverseCacheData();
}

bool AffectsClauseEvaluator::isRelationshipEmpty() {
    return Cache::isCacheEmpty(cache->getAffectsCache());
}
