#include "QueryDb.h"
#include <memory>
#include <algorithm>
#include <iterator>
#include "PkbUtil.h"

QueryDb::QueryDb(std::shared_ptr<ReadStorage> storage) : storage(storage) {}

void QueryDb::addResult(std::shared_ptr<ResultTable> toAdd) {
    if (!toAdd->hasNoResults() && toAdd->getColumnsNamesSet().empty()) {
        // Table will not affect final results
        return;
    }
    results.push_back(toAdd);
    unionFind.unionMultipleItems(toAdd->getColumnsNames());
}

void QueryDb::setSelectedColumns(std::vector<std::pair<SelectClauseItem, DesignEntity>> selectedCols) {
    selectedSynonyms = selectedCols;
    std::vector<std::string> synonymNames;
    for (const auto& i : selectedCols) {
        synonymNames.emplace_back(SelectClause::getSynonym(i.first));
    }
    unionFind.unionMultipleItems(synonymNames);
}

void QueryDb::fillMissingTables() {
    auto allColumnsPresent = getAllColumnsInResults();
    std::vector<std::pair<std::string, DesignEntity>> missingItems;

    for (const auto& selectedItems : selectedSynonyms) {
        std::string syn = SelectClause::getSynonym(selectedItems.first);
        if (!allColumnsPresent.count(syn)) {
            missingItems.emplace_back(syn, selectedItems.second);
        }
    }

    for (const auto& item : missingItems) {
        auto entities = PkbUtil::getEntitiesFromPkb(storage, item.second);
        auto resultTable = ResultTable::createSingleColumnTable(item.first, entities);
        addResult(resultTable);
    }
}

std::unordered_set<std::string> QueryDb::getAllColumnsInResults() {
    std::unordered_set<std::string> res;
    for (const auto& item : results) {
        auto tableCols = item->getColumnsNamesSet();
        res.insert(tableCols.begin(), tableCols.end());
    }
    return res;
}

void QueryDb::sortResultTables() {
    auto comparePredicate = [](std::shared_ptr<ResultTable> const &a, std::shared_ptr<ResultTable> const &b) {
        return a->getNumberOfRows() < b->getNumberOfRows();
    };
    std::sort(results.begin(), results.end(), comparePredicate);
}

std::vector<std::string> QueryDb::getInterestedResults() {
    if (resultTablesHasFalse()) {
        std::vector<std::string> res;
        if (selectedSynonyms.empty()) {
            res.emplace_back("FALSE");
        }
        return res;
    }

    fillMissingTables();
    sortResultTables();

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
    for (auto item : selectedSynonyms) {
        if (SelectClause::isAttribute(item.first)) {
            auto attributeRef = std::get<AttributeReference>(item.first);
            // E.g r.stmt#, get values of column r
            auto synonymValues = interestedResults->getColumnOrderedValues(attributeRef.getSynonym());
            // synonym values is transformed in place
            mapAttribute(attributeRef, synonymValues, storage);
            interestedResults->insertCol(SelectClause::getString(item.first), synonymValues);
        }
    }
}

std::vector<std::string> QueryDb::getInterestedColumns() {
    std::vector<std::string> res;
    for (auto i : selectedSynonyms) {
        res.push_back(SelectClause::getString(i.first));
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
