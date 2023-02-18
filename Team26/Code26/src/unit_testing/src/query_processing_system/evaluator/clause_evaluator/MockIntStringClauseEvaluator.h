#pragma once
#include "query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/IntStringClauseEvaluator.h"
#include "query_processing_system/parser/Argument.h"
#include <unordered_set>
#include <unordered_map>
#include <string>

class MockIntStringClauseEvaluator : public IntStringClauseEvaluator {
 public:
    MockIntStringClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int, std::unordered_set<std::string>> getRelationshipManager(StoragePointer storage) override;

    std::unordered_map<std::string, std::unordered_set<int>>
    getOppositeRelationshipManager(StoragePointer storage) override;

    std::shared_ptr<ResultTable> getClauseResult();
};
