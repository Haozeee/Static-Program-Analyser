#include "ModifiesPClauseEvaluator.h"

ModifiesPClauseEvaluator::ModifiesPClauseEvaluator(Argument left, Argument right)
    : StringStringClauseEvaluator(left, right) {}

StringStringMap ModifiesPClauseEvaluator::getRelationshipManager() {
    return storage->getModifiesPManager()->getAllRelationshipEntries();
}

StringStringMap ModifiesPClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getModifiesPManager()->getAllReversedRelationshipEntries();
}
