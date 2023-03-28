#include "NextClauseEvaluator.h"

NextClauseEvaluator::NextClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

StmtStmtMap NextClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getNextMap(interestedValues);
}

StmtStmtMap NextClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getNextReverseMap(interestedValues);
}

bool NextClauseEvaluator::isEmptyRelation() {
    return storage->isNextEmpty();
}
