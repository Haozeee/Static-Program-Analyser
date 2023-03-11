#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right, storage) {}

std::unordered_map<std::string, std::unordered_set<std::string>>
UsesPClauseEvaluator::getRelationshipManager() {
    return storage->getUsesPManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<std::string>>
UsesPClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getUsesPManager()->getAllReversedRelationshipEntries();
}
