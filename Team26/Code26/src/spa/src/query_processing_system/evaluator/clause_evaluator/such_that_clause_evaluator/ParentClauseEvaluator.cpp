#include "ParentClauseEvaluator.h"

ParentClauseEvaluator::ParentClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> ParentClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    return {};
}
