#include "QueryEvaluator.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ReadStorage> storage)
    : query(query), storage(storage), queryResults(QueryDb(storage)), cache(std::make_shared<Cache>(storage)) {}

QueryDb QueryEvaluator::evaluateQuery() {
    evaluateSelectClause();

    evaluateClauses();

    return queryResults;
}

void QueryEvaluator::evaluateClauses() {
    for (Clause* clause : query->getAllClauses()) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(storage, cache);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
        if (clauseResultTable->hasNoResults()) {
            // No need to evaluate the remaining clause.
            break;
        }
    }

}

void QueryEvaluator::evaluateSelectClause() {
    std::vector<std::pair<SelectClauseItem, DesignEntity>> selectedCols;
    auto selectClause = query->getSelectClause();
    auto selectClausesItems = selectClause->getSelectClauseItems();
    for (const SelectClauseItem& item : *selectClausesItems) {
        std::string identity = SelectClause::getSynonym(item);
        selectedCols.emplace_back(item, query->getSynonymDesignEntity(identity));
    }
    queryResults.setSelectedColumns(selectedCols);
}
