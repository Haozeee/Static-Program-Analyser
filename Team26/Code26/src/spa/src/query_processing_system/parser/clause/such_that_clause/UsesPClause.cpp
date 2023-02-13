#include "UsesPClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/UsesSClauseEvaluator.h"

UsesPClause::UsesPClause(Argument leftArg, Argument rightArg)
    : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* UsesPClause::getClauseEvaluator() {
    return new UsesSClauseEvaluator(getLeftArg(), getRightArg());
}
