#include "ModifiesPClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ModifiesPClauseEvaluator.h"

ModifiesPClause::ModifiesPClause(Argument leftArg, Argument rightArg)
        : StringStringClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ModifiesPClause::getClauseEvaluator() {
    return new ModifiesPClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> ModifiesPClause::getValidRightDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::VARIABLE,
    };
}
