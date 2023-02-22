#include "CallsClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/UsesSClauseEvaluator.h"

CallsClause::CallsClause(Argument leftArg, Argument rightArg)
        : StringStringClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* CallsClause::getClauseEvaluator() {
    // TODO(Hao Ze) - Change to be able to build for milestone 1
    return new UsesSClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> CallsClause::getValidRightDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::PROCEDURE,
    };
}
