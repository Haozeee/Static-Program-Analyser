#include "MockIntStringClause.h"
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/ModifiesSClauseEvaluator.h"

MockIntStringClause::MockIntStringClause(Argument left, Argument right)
        : IntStringClause(left, right) {}

ClauseEvaluator* MockIntStringClause::getClauseEvaluator() {
    return new ModifiesSClauseEvaluator(getLeftArg(), getRightArg());
}
