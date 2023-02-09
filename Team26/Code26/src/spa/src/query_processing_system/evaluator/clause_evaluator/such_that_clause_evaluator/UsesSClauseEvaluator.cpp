#include "UsesSClauseEvaluator.h"

UsesSClauseEvaluator::UsesSClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> UsesSClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    return {};
}
