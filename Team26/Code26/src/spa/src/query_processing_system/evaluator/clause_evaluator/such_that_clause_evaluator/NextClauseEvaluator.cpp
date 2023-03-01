#include "NextClauseEvaluator.h"

NextClauseEvaluator::NextClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<int>> NextClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    // TODO(Hao Ze) - Change to next manager when implemented
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

std::unordered_map<int, std::unordered_set<int>>
NextClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    // TODO(Hao Ze) - Change to next manager when implemented
    return storage->getFollowsManager()->getAllRelationshipEntries();
}
