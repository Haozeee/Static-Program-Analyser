#include "ParentClause.h"
#include <utility>
#include <unordered_set>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentClauseEvaluator.h"

ParentClause::ParentClause(Argument leftArg, Argument rightArg)
        : IntIntClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ParentClause::getClauseEvaluator() {
    return new ParentClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> ParentClause::getValidLeftDesignEntity() {
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

std::unordered_set<DesignEntity> ParentClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
