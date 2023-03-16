#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/IntIntClauseEvaluator.h"
#include "query_processing_system/parser/Argument.h"

class MockIntIntClauseEvaluator : public IntIntClauseEvaluator {
 public:
    MockIntIntClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int, std::unordered_set<int>> getRelationshipManager() override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager() override;

    std::shared_ptr<ResultTable> getClauseResult();
};
