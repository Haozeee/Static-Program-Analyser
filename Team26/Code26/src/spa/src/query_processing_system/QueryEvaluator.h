#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "parser/Query.h"
#include "evaluator/QueryDb.h"
#include "parser/DesignEntity.h"
#include "evaluator/PkbUtil.h"
#include "evaluator/clause_evaluator/cache/Cache.h"

class QueryEvaluator {
 private:
    Query* query;

    QueryDb queryResults;

    std::shared_ptr<ReadStorage> storage;

    std::shared_ptr<Cache> cache;

    /**
     * Evaluate the select clauses in the query.
     */
    void evaluateSelectClause();

    /**
     * Evaluate the such that clauses in the query.
     */
    void evaluateSuchThatClause();

    /**
     * Evaluate the pattern clauses in the query.
     */
    void evaluatePatternClause();

    /**
     * Evaluate the with clauses in the query.
     */
    void evaluateWithClause();

 public:
    explicit QueryEvaluator(Query* query, std::shared_ptr<ReadStorage> storage);

    QueryDb evaluateQuery();
};
