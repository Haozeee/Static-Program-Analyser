#include "FollowsClauseEvaluator.h"

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap FollowsClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getFollowsManager());
}

StmtStmtMap FollowsClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getFollowsManager());
}

bool FollowsClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getFollowsManager());
}
