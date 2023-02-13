#include "FollowsTClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/FollowsTClauseEvaluator.h"

FollowsTClause::FollowsTClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* FollowsTClause::getClauseEvaluator() {
    return new FollowsTClauseEvaluator(getLeftArg(), getRightArg());
}

ValidArgumentType FollowsTClause::getValidArgumentType() {
    return std::make_pair(stmtRef, stmtRef);
}

ValidDesignEntity FollowsTClause::getValidDesignEntity() {
    return std::make_pair(allStatements, allStatements);
}