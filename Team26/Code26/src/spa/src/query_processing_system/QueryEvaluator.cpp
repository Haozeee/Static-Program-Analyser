#include "QueryEvaluator.h"
#include <algorithm>
#include <iterator>
#include "evaluator/ResultTable.h"

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ReadStroage> storage)
    : query(query), storage(storage), queryResults(QueryDb()) {}

QueryDb QueryEvaluator::evaluateQuery() {
    // Evaluate select clauses
    evaluateSelectClause();

    // Evaluate such that clauses
    evaluateSuchThatClause();

    // Evaluate pattern clauses
    evaluatePatternClause();

    // Return QueryResult
    return queryResults;
}

void QueryEvaluator::evaluateSuchThatClause() {
    for (SuchThatClause* clause : query->getSuchThatClauses()) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(storage);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
    }
}

void QueryEvaluator::evaluatePatternClause() {
    for (PatternClause* clause : query->getPatternClause()) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(storage);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
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
        auto resultTable = ResultTable::createSingleColumnTable(syn->getIdent(), entities);
        queryResults.addResult(resultTable);
        queryResults.setSelectedColumn(syn->getIdent());
    }
}
