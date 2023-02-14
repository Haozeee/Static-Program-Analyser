#include "AssignPatternClauseEvaluator.h"

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg,
                                StringExpression rightArg)
    : PatternClauseEvaluator(patternArg, leftArg, rightArg) {}

std::shared_ptr<ResultTable> AssignPatternClauseEvaluator::evaluateClause(std::shared_ptr<ReadStroage> storage) {
    return clauseResultTable;
}
