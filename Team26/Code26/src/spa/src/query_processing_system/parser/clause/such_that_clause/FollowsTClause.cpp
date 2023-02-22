#include "FollowsTClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/FollowsTClauseEvaluator.h"

FollowsTClause::FollowsTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* FollowsTClause::getClauseEvaluator() {
    return new FollowsTClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> FollowsTClause::getValidLeftDesignEntity() {
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

std::unordered_set<DesignEntity> FollowsTClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
