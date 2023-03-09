#include "WhilePatternClause.h"

#include <utility>
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/WhilePatternClauseEvaluator.h"

WhilePatternClause::WhilePatternClause(Argument pattern, Argument left, StringExpression right)
        : PatternClause(std::move(pattern), std::move(left), std::move(right)) {}

ClauseEvaluator* WhilePatternClause::getClauseEvaluator() {
    return new WhilePatternClauseEvaluator(getPatternArg(), getLeftArg(), getRightArg());
}
