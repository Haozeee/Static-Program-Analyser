#include "FollowsClauseEvaluator.h"

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

IntIntMap FollowsClauseEvaluator::getRelationshipManager() {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

IntIntMap FollowsClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}
