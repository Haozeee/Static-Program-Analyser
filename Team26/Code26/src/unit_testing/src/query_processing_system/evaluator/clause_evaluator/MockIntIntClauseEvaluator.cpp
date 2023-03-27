#include "MockIntIntClauseEvaluator.h"

MockIntIntClauseEvaluator::MockIntIntClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap MockIntIntClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    StmtStmtMap res {
            {1, {2, 3}},
            {3, {4}},
            {4, {5, 6, 7}}
    };
    return res;
}

StmtStmtMap MockIntIntClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    StmtStmtMap res {
            {2, {1}},
            {3, {1}},
            {4, {3}},
            {5, {4}},
            {6, {4}},
            {7, {4}},
    };
    return res;
}

bool MockIntIntClauseEvaluator::isEmptyRelation() {
    return false;
}

std::shared_ptr<ResultTable> MockIntIntClauseEvaluator::getClauseResult() {
    return clauseResultTable;
}
