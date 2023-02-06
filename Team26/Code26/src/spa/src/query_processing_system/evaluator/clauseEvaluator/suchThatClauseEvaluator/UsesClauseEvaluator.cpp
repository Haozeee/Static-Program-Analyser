#include "UsesClauseEvaluator.h"

UsesClauseEvaluator::UsesClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> UsesClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    return {};
}
