#include "AssignPatternClause.h"

#include <utility>
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/AssignPatternClauseEvaluator.h"

AssignPatternClause::AssignPatternClause(Argument pattern, Argument left, StringExpression right)
    : PatternClause(std::move(pattern), std::move(left), std::move(right)) {}

ClauseEvaluator* AssignPatternClause::getClauseEvaluator() {
    return new AssignPatternClauseEvaluator(getPatternArg(), getLeftArg(), getRightArg());
}
