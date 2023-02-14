#include "UsesPClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/UsesSClauseEvaluator.h"

UsesPClause::UsesPClause(Argument leftArg, Argument rightArg)
    : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* UsesPClause::getClauseEvaluator() {
    return new UsesSClauseEvaluator(getLeftArg(), getRightArg());
}

ValidArgumentType UsesPClause::getValidArgumentType() {
    return std::make_pair(entRef, entRef);
}

ValidDesignEntity UsesPClause::getValidDesignEntity() {
    return std::make_pair(procedureOnly, variableOnly);
}
