#include "CallsTClauseEvaluator.h"

CallsTClauseEvaluator::CallsTClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

EntityEntityMap CallsTClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return storage->getCallsTMap(interestedValues);
}

EntityEntityMap CallsTClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getCallsTReverseMap(interestedValues)
}

bool CallsTClauseEvaluator::isEmptyRelation() {
    return storage->isCallsEmpty();
}
