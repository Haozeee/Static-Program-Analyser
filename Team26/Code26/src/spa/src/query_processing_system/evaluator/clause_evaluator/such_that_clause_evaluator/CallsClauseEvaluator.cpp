#include "CallsClauseEvaluator.h"

CallsClauseEvaluator::CallsClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getCallPManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<std::string>>
CallsClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getCallPManager()->getAllReversedRelationshipEntries();
}

void CallsClauseEvaluator::handleRightWildcard() {
    rightArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::PROCEDURE);
}
