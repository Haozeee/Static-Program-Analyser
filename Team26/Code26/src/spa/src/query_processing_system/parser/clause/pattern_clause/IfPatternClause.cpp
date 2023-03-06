#include "IfPatternClause.h"
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/IfPatternClauseEvaluator.h"

IfPatternClause::IfPatternClause(Argument pattern, Argument left, StringExpression right)
        : PatternClause(pattern, left, right) {}

ClauseEvaluator* IfPatternClause::getClauseEvaluator() {
    return new IfPatternClauseEvaluator(getPatternArg(), getLeftArg());
}
