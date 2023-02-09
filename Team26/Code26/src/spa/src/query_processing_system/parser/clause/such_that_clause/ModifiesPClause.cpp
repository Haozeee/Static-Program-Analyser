#include "ModifiesPClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ModifiesPClauseEvaluator.h"

ModifiesPClause::ModifiesPClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ModifiesPClause::getClauseEvaluator() {
    return new ModifiesPClauseEvaluator(getLeftArg(), getRightArg());
}
