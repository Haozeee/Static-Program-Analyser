#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

EntityEntityMap UsesPClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getUsesPManager());
}

EntityEntityMap UsesPClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getUsesPManager());
}

bool UsesPClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getUsesPManager());
}
