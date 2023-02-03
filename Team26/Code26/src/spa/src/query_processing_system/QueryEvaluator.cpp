#include "QueryEvaluator.h"
#include "evaluator/QueryResult.h"

QueryEvaluator::QueryEvaluator(Query* query) : query(query) {};

QueryResult QueryEvaluator::evaluateQuery() {
    // Evaluate select clauses
    evaluateSelectClause();

    // Get filters

    // Apply filters to result

    // Return QueryResult
    return queryResult;
}

void QueryEvaluator::evaluateSelectClause() {
    auto selectClauses = query->getSelectClause()->getSelectClauseItems();
    // Loop through select clauses
    for (SelectClauseItem item : *selectClauses) {
        std::shared_ptr<Synonym> syn = std::get<std::shared_ptr<Synonym>>(item);
        // Add identity to results
        queryResult.addNewIdentity(syn->ident);
        // Get data from pkb
    }
}
