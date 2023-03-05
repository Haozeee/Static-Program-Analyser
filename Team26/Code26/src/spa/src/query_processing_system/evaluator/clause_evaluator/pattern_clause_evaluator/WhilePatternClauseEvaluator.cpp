#include "WhilePatternClauseEvaluator.h"

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : PatternClauseEvaluator(patternArg, leftArg, StringExpression(true)) {}

std::shared_ptr<ResultTable> WhilePatternClauseEvaluator::evaluateClause(std::shared_ptr<ReadStorage> storage) {
    return clauseResultTable;
}
