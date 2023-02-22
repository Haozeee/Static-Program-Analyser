#include "AffectsTClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentTClauseEvaluator.h"

AffectsTClause::AffectsTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* AffectsTClause::getClauseEvaluator() {
    // TODO(Hao Ze) - Change to be able to build for milestone 1
    return new ParentTClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> AffectsTClause::getValidLeftDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::ASSIGN,
    };
}

std::unordered_set<DesignEntity> AffectsTClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
