#include "ModifiesPClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ModifiesSClauseEvaluator.h"

ModifiesPClause::ModifiesPClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ModifiesPClause::getClauseEvaluator() {
    // TODO(Hao Ze) - Change to be able to build for now
    return new ModifiesSClauseEvaluator(getLeftArg(), getRightArg());
}
