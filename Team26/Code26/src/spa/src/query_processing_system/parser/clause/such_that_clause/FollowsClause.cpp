#include "FollowsClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"

FollowsClause::FollowsClause(Argument leftArg, Argument rightArg)
    : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* FollowsClause::getClauseEvaluator() {
    return new FollowsClauseEvaluator(getLeftArg(), getRightArg());
}
