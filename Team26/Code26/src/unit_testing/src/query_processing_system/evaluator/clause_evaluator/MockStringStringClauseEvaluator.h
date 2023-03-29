#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/StringStringClauseEvaluator.h"
#include "query_processing_system/parser/Argument.h"

class MockStringStringClauseEvaluator : public StringStringClauseEvaluator {
public:
    MockStringStringClauseEvaluator(Argument left, Argument right);

    EntityEntityMap getRelationshipMap(EntitySet &interestedValues) override;

    EntityEntityMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

    std::shared_ptr<ResultTable> getClauseResult();
};
