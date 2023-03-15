#include "NextClauseEvaluator.h"

NextClauseEvaluator::NextClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<int>> NextClauseEvaluator::getRelationshipManager() {
    return storage->getNextManager()->getAllRelationshipEntries();
}

std::unordered_map<int, std::unordered_set<int>>
NextClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getNextManager()->getAllReversedRelationshipEntries();
}
