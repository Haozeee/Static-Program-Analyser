#include "FollowsClauseEvaluator.h"

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap FollowsClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getFollowsMap(interestedValues);
}

StmtStmtMap FollowsClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getFollowsReverseMap(interestedValues);
}

bool FollowsClauseEvaluator::isEmptyRelation() {
    return storage->isFollowsEmpty();
}
