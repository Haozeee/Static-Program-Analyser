#pragma once
#include <memory>
#include "parser/Query.h"
#include "evaluator/QueryResult.h"
#include "../program_knowledge_base/ReadOnlyStorage.h"

class QueryEvaluator {
 private:
    Query* query;
    QueryResult queryResult;
    std::shared_ptr<ReadOnlyStorage> storage;

    /**
     * Evaluate the select clauses in the query.
     */
    void evaluateSelectClause();

 public:
    explicit QueryEvaluator(Query* query, std::shared_ptr<ReadOnlyStorage> storage);

    QueryResult evaluateQuery();
};
