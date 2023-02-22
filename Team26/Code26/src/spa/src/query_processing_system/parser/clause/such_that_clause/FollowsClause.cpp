#include "FollowsClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"

FollowsClause::FollowsClause(Argument leftArg, Argument rightArg)
    : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* FollowsClause::getClauseEvaluator() {
    return new FollowsClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> FollowsClause::getValidLeftDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::STMT,
            DesignEntity::ASSIGN,
            DesignEntity::WHILE,
            DesignEntity::CALL,
            DesignEntity::PRINT,
            DesignEntity::READ,
            DesignEntity::IF,
    };
}

std::unordered_set<DesignEntity> FollowsClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
