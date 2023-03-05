#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

std::unordered_map<std::string, std::unordered_set<std::string>>
UsesPClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getUsesPManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<std::string>>
UsesPClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getUsesPManager()->getAllReversedRelationshipEntries();
}
