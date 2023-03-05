#include "IfPatternClauseEvaluator.h"

IfPatternClauseEvaluator::IfPatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : PatternClauseEvaluator(patternArg, leftArg, StringExpression(true)) {}

std::shared_ptr<ResultTable> IfPatternClauseEvaluator::evaluateClause(std::shared_ptr<ReadStorage> storage) {
    return clauseResultTable;
}
