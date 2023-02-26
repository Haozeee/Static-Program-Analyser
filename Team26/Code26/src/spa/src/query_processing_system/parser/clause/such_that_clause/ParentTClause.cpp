#include "ParentTClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentTClauseEvaluator.h"

ParentTClause::ParentTClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ParentTClause::getClauseEvaluator() {
    return new ParentTClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> ParentTClause::getValidLeftDesignEntity() {
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

std::unordered_set<DesignEntity> ParentTClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
