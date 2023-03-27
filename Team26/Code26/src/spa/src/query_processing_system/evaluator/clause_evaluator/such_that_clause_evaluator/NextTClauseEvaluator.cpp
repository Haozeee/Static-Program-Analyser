#include "NextTClauseEvaluator.h"

NextTClauseEvaluator::NextTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap NextTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getNextTMap(interestedValues);
}

StmtStmtMap NextTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getNextReverseMap(interestedValues);
}

bool NextTClauseEvaluator::isEmptyRelation() {
    return storage->isNextEmpty();
}
