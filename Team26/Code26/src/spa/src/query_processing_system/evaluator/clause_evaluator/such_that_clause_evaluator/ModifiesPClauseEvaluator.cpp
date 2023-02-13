#include "ModifiesPClauseEvaluator.h"

ModifiesPClauseEvaluator::ModifiesPClauseEvaluator(Argument left, Argument right)
        : SuchThatClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>>
ModifiesPClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>>
ModifiesPClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}

void ModifiesPClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void ModifiesPClauseEvaluator::setRightArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void ModifiesPClauseEvaluator::setLeftAndRightArgResult(std::unordered_set<int> resultLeft,
                                                     std::unordered_set<int> resultRight) {
    clauseResultTable = ResultTable::createDoubleColumnTable(leftArg.getValue(),
                                                             PkbUtil::intSetToStringSet(resultLeft),
                                                             rightArg.getValue(),
                                                             PkbUtil::intSetToStringSet(resultRight));
}


std::unordered_set<int> ModifiesPClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> ModifiesPClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

std::shared_ptr<ResultTable> ModifiesPClauseEvaluator::evaluateClause(StoragePointer storage) {
    return clauseResultTable;
}
