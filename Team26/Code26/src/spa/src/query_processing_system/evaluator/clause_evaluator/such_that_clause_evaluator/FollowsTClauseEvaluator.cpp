#include "FollowsTClauseEvaluator.h"

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

IntIntMap FollowsTClauseEvaluator::getRelationshipManager() {
    return storage->getFollowsTManager()->getAllRelationshipEntries();
}

IntIntMap FollowsTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getFollowsTManager()->getAllReversedRelationshipEntries();
}
