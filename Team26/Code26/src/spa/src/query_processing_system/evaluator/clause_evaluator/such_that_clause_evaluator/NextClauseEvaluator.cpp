#include "NextClauseEvaluator.h"

NextClauseEvaluator::NextClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

IntIntMap NextClauseEvaluator::getRelationshipManager() {
    return storage->getNextManager()->getAllRelationshipEntries();
}

IntIntMap NextClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getNextManager()->getAllReversedRelationshipEntries();
}
