#include "FollowsTClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/FollowsTClauseEvaluator.h"

FollowsTClause::FollowsTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* FollowsTClause::getClauseEvaluator() {
    return new FollowsTClauseEvaluator(getLeftArg(), getRightArg());
}
