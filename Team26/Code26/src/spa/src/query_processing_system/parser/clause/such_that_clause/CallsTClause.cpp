#include "CallsTClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/CallsTClauseEvaluator.h"

CallsTClause::CallsTClause(Argument leftArg, Argument rightArg)
        : StringStringClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* CallsTClause::getClauseEvaluator() {
    return new CallsTClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> CallsTClause::getValidRightDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::PROCEDURE,
    };
}
