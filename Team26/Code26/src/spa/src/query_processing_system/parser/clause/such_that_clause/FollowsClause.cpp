#include "FollowsClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"

FollowsClause::FollowsClause(Argument leftArg, Argument rightArg)
    : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* FollowsClause::getClauseEvaluator() {
    return new FollowsClauseEvaluator(getLeftArg(), getRightArg());
}

ValidArgumentType FollowsClause::getValidArgumentType() {
    return std::make_pair(stmtRef, stmtRef);
}

ValidDesignEntity FollowsClause::getValidDesignEntity() {
    return std::make_pair(allStatements, allStatements);
}
