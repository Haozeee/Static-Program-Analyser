#pragma once
#include "parser/Query.h"
#include "evaluator/QueryResult.h"

class QueryEvaluator {
private:
    Query* query;
    QueryResult queryResult;

    void evaluateSelectClause();

public:
    explicit QueryEvaluator(Query* query);

    QueryResult evaluateQuery();
};
