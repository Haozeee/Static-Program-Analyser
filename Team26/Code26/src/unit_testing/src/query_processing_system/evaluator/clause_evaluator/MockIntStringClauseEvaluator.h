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

    std::unordered_map<int, std::unordered_set<std::string>> getRelationshipManager() override;

    std::unordered_map<std::string, std::unordered_set<int>> getOppositeRelationshipManager() override;

    std::shared_ptr<ResultTable> getClauseResult();
};
