#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "parser/Query.h"
#include "evaluator/QueryDb.h"
#include "parser/DesignEntity.h"
#include "evaluator/PkbUtil.h"

class QueryEvaluator {
 private:
    Query* query;

    QueryDb queryResults;

    std::shared_ptr<ReadStroage> storage;

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

 public:
    explicit QueryEvaluator(Query* query, std::shared_ptr<ReadStroage> storage);

    QueryDb evaluateQuery();
};
