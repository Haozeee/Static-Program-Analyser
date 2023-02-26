#include "AffectsClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentTClauseEvaluator.h"

AffectsClause::AffectsClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* AffectsClause::getClauseEvaluator() {
    // TODO(Hao Ze) - Change to be able to build for milestone 1
    return new ParentTClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> AffectsClause::getValidLeftDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::ASSIGN,
    };
}

std::unordered_set<DesignEntity> AffectsClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
