#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> UsesPClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    return {};
}
