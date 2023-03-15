#include "FollowsTClauseEvaluator.h"

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>>
FollowsTClauseEvaluator::getRelationshipManager() {
    return storage->getFollowsTManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>>
FollowsTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getFollowsTManager()->getAllReversedRelationshipEntries();
}
