#include "ModifiesPClauseEvaluator.h"

ModifiesPClauseEvaluator::ModifiesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

EntityEntityMap ModifiesPClauseEvaluator::getRelationshipManager() {
    return storage->getModifiesPManager()->getAllRelationshipEntries();
}

EntityEntityMap ModifiesPClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getModifiesPManager()->getAllReversedRelationshipEntries();
}
