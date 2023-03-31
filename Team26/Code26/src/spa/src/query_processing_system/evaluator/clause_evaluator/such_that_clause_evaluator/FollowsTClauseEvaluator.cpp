#include "FollowsTClauseEvaluator.h"

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap FollowsTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getFollowsTMap(interestedValues);
}

StmtStmtMap FollowsTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getFollowsTReverseMap(interestedValues);
}

bool FollowsTClauseEvaluator::isEmptyRelation() {
    return storage->isFollowsEmpty();
}
