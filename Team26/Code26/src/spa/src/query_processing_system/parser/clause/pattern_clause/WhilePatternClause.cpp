#include "WhilePatternClause.h"
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/WhilePatternClauseEvaluator.h"

WhilePatternClause::WhilePatternClause(Argument pattern, Argument left, StringExpression right)
        : PatternClause(pattern, left, right) {}

ClauseEvaluator* WhilePatternClause::getClauseEvaluator() {
    return new WhilePatternClauseEvaluator(getPatternArg(), getLeftArg());
}
