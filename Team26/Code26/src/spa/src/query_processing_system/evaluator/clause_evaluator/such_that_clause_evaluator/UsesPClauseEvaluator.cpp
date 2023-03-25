#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

StringStringMap UsesPClauseEvaluator::getRelationshipManager() {
    return storage->getUsesPManager()->getAllRelationshipEntries();
}

StringStringMap UsesPClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getUsesPManager()->getAllReversedRelationshipEntries();
}
