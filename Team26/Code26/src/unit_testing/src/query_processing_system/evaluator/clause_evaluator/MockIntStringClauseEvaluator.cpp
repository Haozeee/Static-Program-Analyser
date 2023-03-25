#include "MockIntStringClauseEvaluator.h"

MockIntStringClauseEvaluator::MockIntStringClauseEvaluator(Argument left, Argument right)
    : IntStringClauseEvaluator(left, right) {}

StmtEntityMap MockIntStringClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    StmtEntityMap res {
            {1, {"v1", "v2"}},
            {3, {"v1"}},
            {4, {"v4", "v5", "v6"}}
    };
    return res;
}

EntityStmtMap MockIntStringClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    EntityStmtMap res;
    return res;
}

bool MockIntStringClauseEvaluator::isEmptyRelation() {
    return false;
}

std::shared_ptr<ResultTable> MockIntStringClauseEvaluator::getClauseResult() {
    return clauseResultTable;
}
