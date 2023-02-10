#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
        : SuchThatClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>> ParentTClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>>
ParentTClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}

void ParentTClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(leftArg.getValue(), PkbUtil::intSetToStringSet(result));
}

void ParentTClauseEvaluator::setRightArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(rightArg.getValue(), PkbUtil::intSetToStringSet(result));
}


std::unordered_set<int> ParentTClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> ParentTClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

std::shared_ptr<ClauseResult> ParentTClauseEvaluator::evaluateClause(StoragePointer storage) {
    return clauseResult;
}
