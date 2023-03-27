#include "MockIntIntClauseEvaluator.h"

MockIntIntClauseEvaluator::MockIntIntClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap MockIntIntClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getFollowsMap(interestedValues);
}

StmtStmtMap MockIntIntClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getFollowsReverseMap(interestedValues);
}

bool MockIntIntClauseEvaluator::isEmptyRelation() {
    return storage->isFollowsEmpty();
}

std::shared_ptr<ResultTable> MockIntIntClauseEvaluator::getClauseResult() {
    return clauseResultTable;
}
