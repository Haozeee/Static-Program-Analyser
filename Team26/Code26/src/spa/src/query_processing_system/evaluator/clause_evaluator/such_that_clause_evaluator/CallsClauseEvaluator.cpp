#include "CallsClauseEvaluator.h"

CallsClauseEvaluator::CallsClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

StringStringMap CallsClauseEvaluator::getRelationshipManager() {
    return storage->getCallsPManager()->getAllRelationshipEntries();
}

StringStringMap CallsClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getCallsPManager()->getAllReversedRelationshipEntries();
}
