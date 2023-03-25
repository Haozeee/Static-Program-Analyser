#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

EntityEntityMap UsesPClauseEvaluator::getRelationshipManager() {
    return storage->getUsesPManager()->getAllRelationshipEntries();
}

EntityEntityMap UsesPClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getUsesPManager()->getAllReversedRelationshipEntries();
}
