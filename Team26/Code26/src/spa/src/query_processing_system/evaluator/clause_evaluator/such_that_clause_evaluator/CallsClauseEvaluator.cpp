#include "CallsClauseEvaluator.h"

CallsClauseEvaluator::CallsClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

EntityEntityMap CallsClauseEvaluator::getRelationshipManager() {
    return storage->getCallsPManager()->getAllRelationshipEntries();
}

EntityEntityMap CallsClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getCallsPManager()->getAllReversedRelationshipEntries();
}
