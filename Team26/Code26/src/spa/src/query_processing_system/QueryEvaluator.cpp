#include "QueryEvaluator.h"
#include <algorithm>
#include <iterator>
#include "evaluator/ResultTable.h"

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ReadOnlyStorage> storage)
    : query(query), storage(storage), queryResults(QueryDb()) {}

QueryDb QueryEvaluator::evaluateQuery() {
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
        // Get respective entities from pkb
        auto entities = PkbUtil::getEntitiesFromPkb(storage, query->getSynonymDesignEntity(syn));
        // Add entities to query result
        auto resultTable = std::make_shared<ResultTable>(syn->getIdent());
        for (auto i : entities) {
            resultTable->insertRow({i});
        }
        queryResults.addResult(resultTable);
    }
}
