#include "CallsTClauseEvaluator.h"

CallsTClauseEvaluator::CallsTClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

EntityEntityMap CallsTClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getCallsTManager());
}

EntityEntityMap CallsTClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getCallsTManager());
}

bool CallsTClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getCallsTManager());
}
