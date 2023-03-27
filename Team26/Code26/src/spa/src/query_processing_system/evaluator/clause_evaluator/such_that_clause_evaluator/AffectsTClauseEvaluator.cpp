#include "AffectsTClauseEvaluator.h"

AffectsTClauseEvaluator::AffectsTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap AffectsTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cache->getAffectsTCache(), interestedValues);
}

StmtStmtMap AffectsTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cache->getAffectsTReverseCache(), interestedValues);
}

bool AffectsTClauseEvaluator::isEmptyRelation() {
    return Cache::isCacheEmpty(cache->getAffectsTCache());
}
