#include "UsesSClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/UsesSClauseEvaluator.h"

UsesSClause::UsesSClause(Argument leftArg, Argument rightArg)
    : IntStringClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* UsesSClause::getClauseEvaluator() {
    return new UsesSClauseEvaluator(getLeftArg(), getRightArg());
}
