#include "FollowsClauseEvaluator.h"

FollowsClauseEvaluator::FollowsClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

bool FollowsClauseEvaluator::evaluateClause() {
    return true;
}