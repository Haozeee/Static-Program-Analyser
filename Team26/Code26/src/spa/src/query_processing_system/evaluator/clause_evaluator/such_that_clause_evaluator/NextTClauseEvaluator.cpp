#include "NextTClauseEvaluator.h"

NextTClauseEvaluator::NextTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap NextTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cache->getNextTCache(), interestedValues);
}

StmtStmtMap NextTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return Cache::getCacheData(cache->getNextTReverseCache(), interestedValues);
}

bool NextTClauseEvaluator::isEmptyRelation() {
    return Cache::isCacheEmpty(cache->getNextTCache());
}
