#include "ParentClause.h"
#include <utility>
#include "../../../evaluator/clause_evaluator/such_that_clause_evaluator/ParentClauseEvaluator.h"

ParentClause::ParentClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

ClauseEvaluator* ParentClause::getClauseEvaluator() {
    return new ParentClauseEvaluator(getLeftArg(), getRightArg());
}

ValidArgumentType ParentClause::getValidArgumentType() {
    return std::make_pair(stmtRef, stmtRef);
}

ValidDesignEntity ParentClause::getValidDesignEntity() {
    return std::make_pair(allStatements, allStatements);
}
