#include "NextClauseEvaluator.h"

NextClauseEvaluator::NextClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<int>> NextClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getNextManager()->getAllRelationshipEntries();
}

std::unordered_map<int, std::unordered_set<int>>
NextClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getNextManager()->getAllReversedRelationshipEntries();
}
