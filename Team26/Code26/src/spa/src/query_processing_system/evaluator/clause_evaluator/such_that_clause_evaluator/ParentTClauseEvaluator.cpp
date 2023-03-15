#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>> ParentTClauseEvaluator::getRelationshipManager() {
    return storage->getParentTManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>> ParentTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getParentTManager()->getAllReversedRelationshipEntries();
}
