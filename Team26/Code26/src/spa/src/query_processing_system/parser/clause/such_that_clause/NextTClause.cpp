#include "NextTClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentTClauseEvaluator.h"

NextTClause::NextTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* NextTClause::getClauseEvaluator() {
    // TODO(Hao Ze) - Change to be able to build for milestone 1
    return new ParentTClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> NextTClause::getValidLeftDesignEntity() {
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

std::unordered_set<DesignEntity> NextTClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
