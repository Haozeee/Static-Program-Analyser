#include "UsesSClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/UsesSClauseEvaluator.h"

UsesSClause::UsesSClause(Argument leftArg, Argument rightArg)
    : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* UsesSClause::getClauseEvaluator() {
    return new UsesSClauseEvaluator(getLeftArg(), getRightArg());
}

ValidArgumentType UsesSClause::getValidArgumentType() {
    return std::make_pair(stmtRef, entRef);
}

ValidDesignEntity UsesSClause::getValidDesignEntity() {
    return std::make_pair(allStatements, variableOnly);
}
