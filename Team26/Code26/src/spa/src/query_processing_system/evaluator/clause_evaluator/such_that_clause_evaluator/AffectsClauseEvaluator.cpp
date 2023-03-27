#include "AffectsClauseEvaluator.h"

AffectsClauseEvaluator::AffectsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap AffectsClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cache->getAffectsCache(), interestedValues);
}

StmtStmtMap AffectsClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return cache->getAffectsReverseCacheData();
}

bool AffectsClauseEvaluator::isEmptyRelation() {
    return Cache::isCacheEmpty(cache->getAffectsCache());
}
