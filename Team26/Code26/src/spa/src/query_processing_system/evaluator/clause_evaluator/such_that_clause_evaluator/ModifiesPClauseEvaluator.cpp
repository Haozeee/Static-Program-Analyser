#include "ModifiesPClauseEvaluator.h"

ModifiesPClauseEvaluator::ModifiesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

std::unordered_map<std::string, std::unordered_set<std::string>>
ModifiesPClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return {};
}

std::unordered_map<std::string, std::unordered_set<std::string>>
ModifiesPClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return {};
}
