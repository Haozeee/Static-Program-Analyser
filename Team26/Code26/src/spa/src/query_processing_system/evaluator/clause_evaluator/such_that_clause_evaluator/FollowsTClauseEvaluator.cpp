#include "FollowsTClauseEvaluator.h"

FollowsTClauseEvaluator::FollowsTClauseEvaluator(Argument left, Argument right)
        : SuchThatClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>>
FollowsTClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>>
FollowsTClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}

void FollowsTClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(leftArg.getValue(), PkbUtil::intSetToStringSet(result));
}

void FollowsTClauseEvaluator::setRightArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(rightArg.getValue(), PkbUtil::intSetToStringSet(result));
}

std::unordered_set<int> FollowsTClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> FollowsTClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

std::shared_ptr<ClauseResult> FollowsTClauseEvaluator::evaluateClause(StoragePointer storage) {
    return clauseResult;
}
