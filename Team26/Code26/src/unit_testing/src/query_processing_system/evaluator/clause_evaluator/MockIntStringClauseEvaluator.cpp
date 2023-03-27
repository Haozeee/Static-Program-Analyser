#include "MockIntStringClauseEvaluator.h"

MockIntStringClauseEvaluator::MockIntStringClauseEvaluator(Argument left, Argument right)
    : IntStringClauseEvaluator(left, right) {}

StmtEntityMap MockIntStringClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getUsesSMap(interestedValues);
}

EntityStmtMap MockIntStringClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getUsesSReverseMap(interestedValues);
}

bool MockIntStringClauseEvaluator::isEmptyRelation() {
    return storage->isUsesSEmpty();
}

std::shared_ptr<ResultTable> MockIntStringClauseEvaluator::getClauseResult() {
    return clauseResultTable;
}
