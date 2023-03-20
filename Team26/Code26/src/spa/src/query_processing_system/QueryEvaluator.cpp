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
    std::vector<std::pair<SelectClauseItem, DesignEntity>> selectedCols;
    auto selectClause = query->getSelectClause();
    auto selectClausesItems = selectClause->getSelectClauseItems();
    for (SelectClauseItem item : *selectClausesItems) {
        std::string identity = SelectClause::getSynonym(item);
        selectedCols.emplace_back(item, query->getSynonymDesignEntity(identity));
    }
    queryResults.setSelectedColumns(selectedCols);
}
