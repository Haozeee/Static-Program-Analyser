#include "QueryEvaluator.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>
#include "query_processing_system/evaluator/clause_evaluator/StorageReader.h"

QueryEvaluator::QueryEvaluator(Query* query, std::shared_ptr<ISourceReader> programmeStorage_) :
    query(query),
    programmeStorage(programmeStorage_),
    queryResults(QueryDb(programmeStorage_)) {}

QueryDb QueryEvaluator::evaluateQuery() {
    evaluateClauses();
    queryResults.evaluateAllClauses();
    evaluateSelectClause();

    return queryResults;
}

void QueryEvaluator::evaluateClauses() {
    auto allClauses = query->getAllClauses();

    if (allClauses.size() > 3) {
        sortClauses(allClauses);
    }

    for (Clause* clause : allClauses) {
        auto clauseEvaluator = clause->getClauseEvaluator();
        auto clauseResultTable = clauseEvaluator->evaluateClause(programmeStorage);
        queryResults.addResult(clauseResultTable);
        delete clauseEvaluator;
        if (clauseResultTable->hasNoResults()) {
            // No need to evaluate the remaining clause.
            break;
        }
    }
}

void QueryEvaluator::sortClauses(std::vector<Clause*> &allClauses) {
    auto sortPredicate = [](Clause* a, Clause* b) {
        return a->getOptimisationPoints() < b->getOptimisationPoints();
    };
    std::sort(allClauses.begin(), allClauses.end(), sortPredicate);
}

void QueryEvaluator::evaluateSelectClause() {
    std::vector<std::pair<SelectClauseItem, DesignEntity>> selectedCols;
    auto colsPresentInResult = queryResults.getAllColumnsInResults();
    auto selectClausesItems = query->getSelectClauseItems();
    for (const SelectClauseItem& item : *selectClausesItems) {
        std::string identity = SelectClause::getSynonym(item);
        DesignEntity de = query->getSynonymDesignEntity(identity);
        selectedCols.emplace_back(item, de);
        if (!colsPresentInResult.count(identity)) {
            auto resultToAdd = ResultTable::createSingleColumnTable(identity, programmeStorage->getEntitiesFromPkb(de));
            queryResults.addResult(resultToAdd);
        }
    }
    queryResults.setSelectedColumns(selectedCols);
}
