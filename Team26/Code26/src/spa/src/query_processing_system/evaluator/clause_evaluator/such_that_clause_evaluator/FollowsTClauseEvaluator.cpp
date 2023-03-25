#include "FollowsTClauseEvaluator.h"

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap FollowsTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getFollowsTManager());
}

StmtStmtMap FollowsTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getFollowsTManager());
}

bool FollowsTClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getFollowsTManager());
}
