#include "CallsClauseEvaluator.h"

CallsClauseEvaluator::CallsClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return {};
}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return {};
}
