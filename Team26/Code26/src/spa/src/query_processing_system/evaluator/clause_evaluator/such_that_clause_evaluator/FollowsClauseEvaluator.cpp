#include "FollowsClauseEvaluator.h"

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap FollowsClauseEvaluator::getRelationshipManager() {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

StmtStmtMap FollowsClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}
