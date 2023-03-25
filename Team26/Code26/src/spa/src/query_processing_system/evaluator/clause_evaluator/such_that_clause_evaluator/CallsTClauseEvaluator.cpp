#include "CallsTClauseEvaluator.h"

CallsTClauseEvaluator::CallsTClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

EntityEntityMap CallsTClauseEvaluator::getRelationshipManager() {
    return storage->getCallsTManager()->getAllRelationshipEntries();
}

EntityEntityMap CallsTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getCallsTManager()->getAllReversedRelationshipEntries();
}
