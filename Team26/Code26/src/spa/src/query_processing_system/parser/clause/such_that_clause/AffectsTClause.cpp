#include "AffectsTClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/AffectsTClauseEvaluator.h"

AffectsTClause::AffectsTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* AffectsTClause::getClauseEvaluator() {
    return new AffectsTClauseEvaluator(getLeftArg(), getRightArg());
}
