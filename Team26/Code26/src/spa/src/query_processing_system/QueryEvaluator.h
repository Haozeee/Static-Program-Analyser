#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "parser/Query.h"
#include "evaluator/QueryResult.h"
#include "parser/DesignEntity.h"
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

    std::unordered_set<std::string> getEntitiesFromPkb(DesignEntity entity);

 public:
    explicit QueryEvaluator(Query* query, std::shared_ptr<ReadOnlyStorage> storage);

    QueryResult evaluateQuery();
};
