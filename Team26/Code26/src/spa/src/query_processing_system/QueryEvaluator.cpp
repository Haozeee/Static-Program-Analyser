#include "QueryEvaluator.h"
#include <algorithm>
#include <iterator>

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ReadOnlyStorage> storage)
    : query(query), storage(storage) {}

QueryResult QueryEvaluator::evaluateQuery() {
    // Evaluate select clauses
    evaluateSelectClause();

    // Evaluate such that clauses
    evaluateSuchThatClause();

    // Return QueryResult
    return queryResult;
}

void QueryEvaluator::evaluateSuchThatClause() {
    for (SuchThatClause* clause : query->getSuchThatClauses()) {
        auto clauseResult = clause->getClauseEvaluator()->evaluateClause(storage);
        queryResult.addClauseResultToQuery(clauseResult);
    }
}

void QueryEvaluator::evaluateSelectClause() {
    auto selectClauses = query->getSelectClause()->getSelectClauseItems();
    // Loop through select clauses
    for (SelectClauseItem item : *selectClauses) {
        std::shared_ptr<Synonym> syn = std::get<std::shared_ptr<Synonym>>(item);
        // Add identity to results
        queryResult.addNewIdentity(syn->ident);
        // Get respective entities from pkb
        auto entities = PkbUtil::getEntitiesFromPkb(storage, query->getSynonymDesignEntity(syn));
        // Add entities to query result
        queryResult.addNewResult(syn->ident, entities);
    }
}
