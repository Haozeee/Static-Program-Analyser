#include "ModifiesPClauseEvaluator.h"

ModifiesPClauseEvaluator::ModifiesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

EntityEntityMap ModifiesPClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getModifiesPManager());
}

EntityEntityMap ModifiesPClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getModifiesPManager());
}

bool ModifiesPClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getModifiesPManager());
}
