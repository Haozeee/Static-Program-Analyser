#include "ParentTClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentTClauseEvaluator.h"

ParentTClause::ParentTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ParentTClause::getClauseEvaluator() {
    return new ParentTClauseEvaluator(getLeftArg(), getRightArg());
}
