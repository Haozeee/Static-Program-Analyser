#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include <vector>
#include "parser/Query.h"
#include "evaluator/QueryDb.h"
#include "parser/DesignEntity.h"
#include "evaluator/clause_evaluator/cache/Cache.h"
#include "evaluator/clause_evaluator/StorageReader.h"

class QueryEvaluator {
 private:
    Query* query;

    std::shared_ptr<ISourceReader> programmeStorage;

    QueryDb queryResults;

    void evaluateClauses();

    static void sortClauses(std::vector<Clause*> &allClauses);

    /**
     * Evaluate the select clauses in the query.
     */
    void evaluateSelectClause();

 public:
    QueryEvaluator(Query* query, std::shared_ptr<ISourceReader> programmeStorage_);

    QueryDb evaluateQuery();
};
