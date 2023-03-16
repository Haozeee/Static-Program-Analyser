#include "QueryEvaluator.h"
#include <algorithm>
#include <iterator>

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ReadStorage> storage)
    : query(query), storage(storage), queryResults(QueryDb(storage)), cache(std::make_shared<Cache>(storage)) {}

QueryDb QueryEvaluator::evaluateQuery() {
    evaluateSelectClause();

    evaluateSuchThatClause();

    evaluatePatternClause();

    evaluateWithClause();

    return queryResults;
}

void QueryEvaluator::evaluateSuchThatClause() {
    for (SuchThatClause* clause : query->getSuchThatClauses()) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(storage, cache);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
        if (clauseResultTable->hasNoResults()) {
            break;
        }
    }
}

void QueryEvaluator::evaluatePatternClause() {
    for (PatternClause* clause : query->getPatternClause()) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(storage);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
        if (clauseResultTable->hasNoResults()) {
            break;
        }
    }
}

void QueryEvaluator::evaluateWithClause() {
    for (WithClause* clause : query->getWithClause()) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(storage);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
        if (clauseResultTable->hasNoResults()) {
            break;
        }
    }
}

void QueryEvaluator::evaluateSelectClause() {
    auto a = query->getSelectClause();
    auto selectClauses = query->getSelectClause()->getSelectClauseItems();
    for (SelectClauseItem item : *selectClauses) {
        std::string identity = SelectClause::getSynonym(item);
        queryResults.addSelectedColumn(item, query->getSynonymDesignEntity(identity));
    }
}
