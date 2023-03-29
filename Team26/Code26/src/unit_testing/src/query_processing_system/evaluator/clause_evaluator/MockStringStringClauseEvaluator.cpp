#include "MockStringStringClauseEvaluator.h"

MockStringStringClauseEvaluator::MockStringStringClauseEvaluator(Argument left, Argument right)
        : StringStringClauseEvaluator(left, right) {}

EntityEntityMap MockStringStringClauseEvaluator::getRelationshipMap(EntitySet &interestedValues) {
    return storage->getCallsMap(interestedValues);
}

EntityEntityMap MockStringStringClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getCallsReverseMap(interestedValues);
}

bool MockStringStringClauseEvaluator::isEmptyRelation() {
    return storage->isCallsEmpty();
}

std::shared_ptr<ResultTable> MockStringStringClauseEvaluator::getClauseResult() {
    return clauseResultTable;
}
