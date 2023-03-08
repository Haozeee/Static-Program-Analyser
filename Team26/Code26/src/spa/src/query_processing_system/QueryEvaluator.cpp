#include "QueryEvaluator.h"
#include <algorithm>
#include <iterator>
#include "evaluator/ResultTable.h"

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ReadStorage> storage)
    : query(query), storage(storage), queryResults(QueryDb(storage)) {}

QueryDb QueryEvaluator::evaluateQuery() {
    // Evaluate select clauses
    evaluateSelectClause();

    // Evaluate such that clauses
    evaluateSuchThatClause();

    // Evaluate pattern clauses
    evaluatePatternClause();

    // Evaluate with clauses
    evaluateWithClause();

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

void QueryEvaluator::evaluateWithClause() {
    for (WithClause* clause : query->getWithClause()) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(storage);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
    }
}

void QueryEvaluator::evaluateSelectClause() {
    auto a = query->getSelectClause();
    auto selectClauses = query->getSelectClause()->getSelectClauseItems();
    // Loop through select clauses
    for (SelectClauseItem item : *selectClauses) {
        std::string identity = SelectClause::getSynonym(item);
        // Get respective entities from pkb
        auto entities = PkbUtil::getEntitiesFromPkb(storage, query->getSynonymDesignEntity(identity));
        // Add entities to query result
        auto resultTable = ResultTable::createSingleColumnTable(identity, entities);
        queryResults.addResult(resultTable);
        queryResults.addSelectedColumn(item);
    }
}
