#include "QueryDb.h"
#include <memory>

QueryDb::QueryDb(std::shared_ptr<ReadStorage> storage) : storage(storage) {}

void QueryDb::addResult(std::shared_ptr<ResultTable> toAdd) {
    results.push_back(toAdd);
}

void QueryDb::addSelectedColumn(SelectClauseItem selectClauseItem) {
    selectedSynonyms.push_back(selectClauseItem);
}

std::vector<std::string> QueryDb::getInterestedResults() {
    std::vector<std::string> res;
    if (resultTablesHasFalse()) {
        if (selectedSynonyms.empty()) {
            res.emplace_back("FALSE");
        }
        return res;
    }

    std::shared_ptr<ResultTable> interestedResults;
    if (!results.empty()) {
        interestedResults = results.front();
        results.pop_front();
    }

    while (!results.empty()) {
        auto table = results.front();
        results.pop_front();
        if (!table->getColumnsNamesSet().empty()) {
            interestedResults = ResultTable::joinTable(interestedResults, table);
        }
    }

    if (selectedSynonyms.empty()) {
        return getBooleanResults(interestedResults);
    }

    // Map attribute references
    mapAttributeReferences(interestedResults);

    // Filter selected columns
    return interestedResults->getInterestedValues(getInterestedColumns());
}

void QueryDb::mapAttributeReferences(std::shared_ptr<ResultTable> interestedResults) {
    for (SelectClauseItem item : selectedSynonyms) {
        if (SelectClause::isAttribute(item)) {
            auto attributeRef = std::get<AttributeReference>(item);
            // E.g r.stmt#, get values of column r
            auto synonymValues = interestedResults->getColumnOrderedValues(attributeRef.getSynonym());
            // synonym values is transformed in place
            mapAttribute(attributeRef, synonymValues, storage);
            interestedResults->insertCol(SelectClause::getString(item), synonymValues);
        }
    }
}

std::vector<std::string> QueryDb::getInterestedColumns() {
    std::vector<std::string> res;
    for (SelectClauseItem i : selectedSynonyms) {
        res.push_back(SelectClause::getString(i));
    }
    return res;
}

std::vector<std::string> QueryDb::getBooleanResults(std::shared_ptr<ResultTable> interestedResults) {
    std::vector<std::string> res;
    // Interested results is not null, has columns but has no rows
    auto isFalse = interestedResults != nullptr && !interestedResults->getColumnsNamesSet().empty()
            && interestedResults->getNumberOfRows() == 0;
    if (isFalse) {
        res.emplace_back("FALSE");
    } else {
        res.emplace_back("TRUE");
    }
    return res;
}

bool QueryDb::resultTablesHasFalse() {
    for (auto i : results) {
        if (i->hasNoResults()) {
            return true;
        }
    }
    return false;
}
