#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "parser/Query.h"
#include "evaluator/QueryDb.h"
#include "parser/DesignEntity.h"
#include "evaluator/clause_evaluator/cache/Cache.h"
#include "evaluator/clause_evaluator/StorageReader.h"

class QueryEvaluator {
 private:
    Query* query;

    QueryDb queryResults;

    std::shared_ptr<ISourceReader> programmeStorage;

    void evaluateClauses();

    /**
     * Evaluate the select clauses in the query.
     */
    void evaluateSelectClause();

 public:
    explicit QueryEvaluator(Query* query, std::shared_ptr<ReadStorage> storage);

    QueryDb evaluateQuery();
};
