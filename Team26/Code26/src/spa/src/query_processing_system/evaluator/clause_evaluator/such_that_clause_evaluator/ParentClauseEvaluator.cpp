#include "ParentClauseEvaluator.h"

ParentClauseEvaluator::ParentClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<int>> ParentClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getParentManager()->getAllRelationshipEntries();
}

std::unordered_map<int, std::unordered_set<int>>
ParentClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getParentManager()->getAllReversedRelationshipEntries();
}
