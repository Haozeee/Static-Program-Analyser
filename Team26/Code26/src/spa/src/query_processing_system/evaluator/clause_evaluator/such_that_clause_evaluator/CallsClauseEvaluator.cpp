#include "CallsClauseEvaluator.h"

CallsClauseEvaluator::CallsClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

EntityEntityMap CallsClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return storage->getCallsMap(interestedValues);
}

EntityEntityMap CallsClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getCallsReverseMap(interestedValues);
}

bool CallsClauseEvaluator::isEmptyRelation() {
    return storage->isCallsEmpty();
}
