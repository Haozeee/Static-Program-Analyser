#include "AffectsTClauseEvaluator.h"

AffectsTClauseEvaluator::AffectsTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {
    cacheable = true;
}

StmtStmtMap AffectsTClauseEvaluator::getRelationshipCache(StmtSet itemsToRead) {
    return Cache::getCacheData(cache->getAffectsTCache(), itemsToRead);
}

StmtStmtMap AffectsTClauseEvaluator::getOppositeRelationshipCache(StmtSet itemsToRead) {
    return Cache::getCacheData(cache->getAffectsTReverseCache(), itemsToRead);
}

StmtStmtMap AffectsTClauseEvaluator::getRelationshipManager() {
    return Cache::getEntireCacheData(cache->getAffectsTCache());
}

StmtStmtMap AffectsTClauseEvaluator::getOppositeRelationshipManager() {
    return Cache::getEntireCacheData(cache->getAffectsTReverseCache());
}

bool AffectsTClauseEvaluator::isRelationshipEmpty() {
    return Cache::isCacheEmpty(cache->getAffectsTCache());
}
