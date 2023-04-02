#include "MockStringStringClause.h"
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/CallsClauseEvaluator.h"

MockStringStringClause::MockStringStringClause (Argument left, Argument right)
        : StringStringClause(left, right) {}

ClauseEvaluator* MockStringStringClause::getClauseEvaluator() {
    return new CallsClauseEvaluator(getLeftArg(), getRightArg());
}

std::unordered_set<DesignEntity> MockStringStringClause::getValidRightDesignEntity() {
    return std::unordered_set<DesignEntity>{
            DesignEntity::PROCEDURE,
    };
}
