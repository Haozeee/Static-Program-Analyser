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
    auto allClauses = query->getAllClauses();

    if (allClauses.size() > 3) {
        // Only sort clauses of size >= 3
        auto sortPredicate = [](Clause* a, Clause* b) {
            return a->getOptimisationPoints() < b->getOptimisationPoints();
        };
        std::sort(allClauses.begin(), allClauses.end(), sortPredicate);
    }

    for (Clause* clause : allClauses) {
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
    auto selectClausesItems = query->getSelectClauseItems();
    for (const SelectClauseItem& item : *selectClausesItems) {
        std::string identity = SelectClause::getSynonym(item);
        selectedCols.emplace_back(item, query->getSynonymDesignEntity(identity));
    }
    queryResults.setSelectedColumns(selectedCols);
}
