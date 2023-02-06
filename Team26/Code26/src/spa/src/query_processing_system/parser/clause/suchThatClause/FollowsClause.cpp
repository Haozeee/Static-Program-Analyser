#include "FollowsClause.h"
#include <utility>
#include "../../../evaluator/clauseEvaluator/suchThatClauseEvaluator/FollowsClauseEvaluator.h"

FollowsClause::FollowsClause(Argument leftArg, Argument rightArg)
    : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* FollowsClause::getClauseEvaluator() {
    return new FollowsClauseEvaluator(getLeftArg(), getRightArg());
}