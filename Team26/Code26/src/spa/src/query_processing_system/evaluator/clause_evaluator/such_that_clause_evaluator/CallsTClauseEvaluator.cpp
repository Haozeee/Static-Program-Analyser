#include "CallsTClauseEvaluator.h"

CallsTClauseEvaluator::CallsTClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

StringStringMap CallsTClauseEvaluator::getRelationshipManager() {
    return storage->getCallsTManager()->getAllRelationshipEntries();
}

StringStringMap CallsTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getCallsTManager()->getAllReversedRelationshipEntries();
}
