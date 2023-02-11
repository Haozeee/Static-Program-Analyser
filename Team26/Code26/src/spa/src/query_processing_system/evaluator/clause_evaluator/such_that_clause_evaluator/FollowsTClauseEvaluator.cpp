#include "FollowsTClauseEvaluator.h"

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>>
FollowsTClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getFollowsTManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>>
FollowsTClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getFollowsTManager()->getAllReversedRelationshipEntries();
}
