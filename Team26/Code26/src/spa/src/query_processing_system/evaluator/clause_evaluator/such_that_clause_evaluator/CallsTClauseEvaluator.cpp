#include "CallsTClauseEvaluator.h"

CallsTClauseEvaluator::CallsTClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsTClauseEvaluator::getRelationshipManager() {
    return storage->getCallsTManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getCallsTManager()->getAllReversedRelationshipEntries();
}
