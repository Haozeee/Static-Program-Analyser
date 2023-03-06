#include "CallsClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/CallsClauseEvaluator.h"

CallsClause::CallsClause(Argument leftArg, Argument rightArg)
        : StringStringClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* CallsClause::getClauseEvaluator() {
    return new CallsClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> CallsClause::getValidRightDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::PROCEDURE,
    };
}
