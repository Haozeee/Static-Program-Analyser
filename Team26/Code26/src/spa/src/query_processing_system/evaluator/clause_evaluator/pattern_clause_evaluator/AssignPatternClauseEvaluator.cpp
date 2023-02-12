#include "AssignPatternClauseEvaluator.h"

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg,
                                StringExpression rightArg)
    : PatternClauseEvaluator(patternArg, leftArg, rightArg) {}

std::shared_ptr<ClauseResult> AssignPatternClauseEvaluator::evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) {
    return clauseResult;
}
