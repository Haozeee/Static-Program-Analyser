#include "WhilePatternClause.h"
#include "AssignPatternClause.h"
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/AssignPatternClauseEvaluator.h"

WhilePatternClause::WhilePatternClause(Argument pattern, Argument left, StringExpression right)
        : PatternClause(pattern, left, right) {}

ClauseEvaluator* WhilePatternClause::getClauseEvaluator() {
    // TODO(Hao Ze) - Change to be able to build for milestone 1
    return new AssignPatternClauseEvaluator(getPatternArg(), getLeftArg(), getRightArg());
}