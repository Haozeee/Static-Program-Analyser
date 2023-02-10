#include "UsesSClauseEvaluator.h"

UsesSClauseEvaluator::UsesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<std::string>> UsesSClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getUsesSManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string , std::unordered_set<int>>
UsesSClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getUsesSManager()->getAllReversedRelationshipEntries();
}
