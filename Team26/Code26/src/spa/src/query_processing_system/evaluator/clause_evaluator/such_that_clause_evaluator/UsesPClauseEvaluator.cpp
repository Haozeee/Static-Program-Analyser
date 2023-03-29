#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

EntityEntityMap UsesPClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return storage->getUsesPMap(interestedValues);
}

EntityEntityMap UsesPClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getUsesPReverseMap(interestedValues);
}

bool UsesPClauseEvaluator::isEmptyRelation() {
    return storage->isUsesPEmpty();
}
