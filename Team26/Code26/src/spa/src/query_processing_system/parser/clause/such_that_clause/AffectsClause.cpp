#include "AffectsClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/AffectsClauseEvaluator.h"

AffectsClause::AffectsClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* AffectsClause::getClauseEvaluator() {
    return new AffectsClauseEvaluator(getLeftArg(), getRightArg());
}
