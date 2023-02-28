#include "NextClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentTClauseEvaluator.h"

NextClause::NextClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* NextClause::getClauseEvaluator() {
    // TODO(Hao Ze) - Change to be able to build for milestone 1
    return new ParentTClauseEvaluator(getLeftArg(), getRightArg());
}
