#include "UsesPClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/UsesPClauseEvaluator.h"

UsesPClause::UsesPClause(Argument leftArg, Argument rightArg)
    : StringStringClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* UsesPClause::getClauseEvaluator() {
    return new UsesPClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> UsesPClause::getValidRightDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::VARIABLE,
    };
}
