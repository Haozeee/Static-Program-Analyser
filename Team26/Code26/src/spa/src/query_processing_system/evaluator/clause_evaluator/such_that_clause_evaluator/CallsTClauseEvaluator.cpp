#include "CallsTClauseEvaluator.h"

CallsTClauseEvaluator::CallsTClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsTClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return {};
}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsTClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return {};
}
