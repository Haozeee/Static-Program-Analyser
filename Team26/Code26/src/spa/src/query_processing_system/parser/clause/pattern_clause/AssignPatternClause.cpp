#include "AssignPatternClause.h"
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/AssignPatternClauseEvaluator.h"

AssignPatternClause::AssignPatternClause(DesignEntity designEntity, Argument left, StringExpression right)
    : PatternClause(designEntity, left, right) {}

ClauseEvaluator* AssignPatternClause::getClauseEvaluator() {
    return new AssignPatternClauseEvaluator(getDesignEntity(), getLeftArg(), getRightArg());
}
