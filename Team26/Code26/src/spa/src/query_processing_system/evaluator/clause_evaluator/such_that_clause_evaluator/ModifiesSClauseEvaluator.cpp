#include "ModifiesSClauseEvaluator.h"

ModifiesSClauseEvaluator::ModifiesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

std::unordered_map<int, std::unordered_set<std::string>>
ModifiesSClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getModifiesSManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string , std::unordered_set<int>>
ModifiesSClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getModifiesSManager()->getAllReversedRelationshipEntries();
}
