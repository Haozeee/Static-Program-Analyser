#include "FollowsClauseEvaluator.h"

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<int>>
FollowsClauseEvaluator::getRelationshipManager() {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

std::unordered_map<int, std::unordered_set<int>>
FollowsClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}
