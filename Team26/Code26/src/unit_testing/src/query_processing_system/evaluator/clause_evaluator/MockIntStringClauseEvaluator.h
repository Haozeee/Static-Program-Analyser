#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/IntStringClauseEvaluator.h"
#include "query_processing_system/parser/Argument.h"

class MockIntStringClauseEvaluator : public IntStringClauseEvaluator {
 public:
    MockIntStringClauseEvaluator(Argument left, Argument right);

    StmtEntityMap getRelationshipMap(StmtSet &interestedValues) override;

    EntityStmtMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

    std::shared_ptr<ResultTable> getClauseResult();
};
