#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>>
ParentTClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>>
ParentTClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}
