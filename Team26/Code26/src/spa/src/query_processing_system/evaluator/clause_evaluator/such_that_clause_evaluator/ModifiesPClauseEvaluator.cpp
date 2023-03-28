#include "ModifiesPClauseEvaluator.h"

ModifiesPClauseEvaluator::ModifiesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

EntityEntityMap ModifiesPClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return storage->getModifiesPMap(interestedValues);
}

EntityEntityMap ModifiesPClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getModifiesPReverseMap(interestedValues);
}

bool ModifiesPClauseEvaluator::isEmptyRelation() {
    return storage->isModifiesPEmpty();
}
