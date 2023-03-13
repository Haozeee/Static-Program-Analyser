#include "ModifiesPClauseEvaluator.h"

ModifiesPClauseEvaluator::ModifiesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

std::unordered_map<std::string, std::unordered_set<std::string>> ModifiesPClauseEvaluator::getRelationshipManager() {
    return storage->getModifiesPManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<std::string>>
ModifiesPClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getModifiesPManager()->getAllReversedRelationshipEntries();
}
