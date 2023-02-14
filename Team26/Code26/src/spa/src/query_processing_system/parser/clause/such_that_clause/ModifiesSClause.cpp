#include "ModifiesSClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ModifiesSClauseEvaluator.h"

ModifiesSClause::ModifiesSClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ModifiesSClause::getClauseEvaluator() {
    return new ModifiesSClauseEvaluator(getLeftArg(), getRightArg());
}

ValidArgumentType ModifiesSClause::getValidArgumentType() {
    return std::make_pair(stmtRef, entRef);
}

ValidDesignEntity ModifiesSClause::getValidDesignEntity() {
    return std::make_pair(allStatements, variableOnly);
}
