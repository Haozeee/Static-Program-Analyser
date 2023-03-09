#include "IfPatternClause.h"

#include <utility>
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/IfPatternClauseEvaluator.h"

IfPatternClause::IfPatternClause(Argument pattern, Argument left, StringExpression right)
        : PatternClause(std::move(pattern), std::move(left), std::move(right)) {}

ClauseEvaluator* IfPatternClause::getClauseEvaluator() {
    return new IfPatternClauseEvaluator(getPatternArg(), getLeftArg(), getRightArg());
}
