#include "CallsClauseEvaluator.h"

CallsClauseEvaluator::CallsClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

EntityEntityMap CallsClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getCallsPManager());
}

EntityEntityMap CallsClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getCallsPManager());
}

bool CallsClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getCallsPManager());
}
