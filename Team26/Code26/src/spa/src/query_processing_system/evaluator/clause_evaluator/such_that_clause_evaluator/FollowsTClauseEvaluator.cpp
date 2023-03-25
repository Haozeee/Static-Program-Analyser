#include "FollowsTClauseEvaluator.h"

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap FollowsTClauseEvaluator::getRelationshipManager() {
    return storage->getFollowsTManager()->getAllRelationshipEntries();
}

StmtStmtMap FollowsTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getFollowsTManager()->getAllReversedRelationshipEntries();
}
