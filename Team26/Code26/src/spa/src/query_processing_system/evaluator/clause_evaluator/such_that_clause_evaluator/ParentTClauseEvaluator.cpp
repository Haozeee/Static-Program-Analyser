#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator(left, right) {}

std::shared_ptr<ClauseResult> ParentTClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    return {};
}
