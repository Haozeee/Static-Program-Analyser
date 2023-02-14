#include "ModifiesSClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ModifiesSClauseEvaluator.h"

ModifiesSClause::ModifiesSClause(Argument leftArg, Argument rightArg)
        : IntStringClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ModifiesSClause::getClauseEvaluator() {
    return new ModifiesSClauseEvaluator(getLeftArg(), getRightArg());
}
