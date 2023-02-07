#include "UsesClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/UsesClauseEvaluator.h"

UsesClause::UsesClause(Argument leftArg, Argument rightArg)
    : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* UsesClause::getClauseEvaluator() {
    return new UsesClauseEvaluator(getLeftArg(), getRightArg());
}
