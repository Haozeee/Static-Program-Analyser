#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "parser/Query.h"
#include "evaluator/QueryDb.h"
#include "parser/DesignEntity.h"
#include "evaluator/PkbUtil.h"
#include "../program_knowledge_base/ReadOnlyStorage.h"

class QueryEvaluator {
 private:
    Query* query;

    QueryDb queryResults;

    std::shared_ptr<ReadOnlyStorage> storage;

    /**
     * Evaluate the select clauses in the query.
     */
    void evaluateSelectClause();

    /**
     * Evalutate the such that clauses in the query.
     */
    void evaluateSuchThatClause();

 public:
    explicit QueryEvaluator(Query* query, std::shared_ptr<ReadOnlyStorage> storage);

    QueryDb evaluateQuery();
};
