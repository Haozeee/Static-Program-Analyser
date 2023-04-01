#include "MockIntIntClause.h"
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"

MockIntIntClause::MockIntIntClause (Argument left, Argument right)
        : IntIntClause(left, right) {}

ClauseEvaluator* MockIntIntClause::getClauseEvaluator() {
    return new FollowsClauseEvaluator(getLeftArg(), getRightArg());
}
