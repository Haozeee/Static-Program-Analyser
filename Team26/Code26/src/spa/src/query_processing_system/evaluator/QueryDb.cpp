#include "QueryDb.h"
#include <memory>
#include <algorithm>
#include <iterator>
#include "PkbUtil.h"

QueryDb::QueryDb(std::shared_ptr<ReadStorage> storage) : storage(storage) {}

void QueryDb::addResult(std::shared_ptr<ResultTable> toAdd) {
    if (!toAdd->hasNoResults() && toAdd->getColumnsNamesSet().empty()) {
        // Table will not affect final results, no need to add
        return;
    }
    results.push_back(toAdd);
    if (!toAdd->hasNoResults()) {
        unionFind.unionMultipleItems(toAdd->getColumnsNames());
    }
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
    std::vector<std::pair<std::string, DesignEntity>> missingColumns;

    for (const auto& selectedItems : selectedSynonyms) {
        std::string syn = SelectClause::getSynonym(selectedItems.first);
        if (!allColumnsPresent.count(syn)) {
            missingColumns.emplace_back(syn, selectedItems.second);
        }
    }

    for (const auto& item : missingColumns) {
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

void QueryDb::sortTables(std::deque<std::shared_ptr<ResultTable>> &tables) {
    auto comparePredicate = [](std::shared_ptr<ResultTable> const &a, std::shared_ptr<ResultTable> const &b) {
        return a->getNumberOfRows() < b->getNumberOfRows();
    };
    std::sort(tables.begin(), tables.end(), comparePredicate);
}

ResultGroups QueryDb::getGroups() {
    ResultGroups groups;
    for (const auto& table : results) {
        if (table->getColumnsNames().empty()) {
            continue;
        }
        std::string root = unionFind.find(table->getColumnsNames().at(0));
        if (groups.count(root)) {
            groups.at(root).push_back(table);
        } else {
            std::deque<std::shared_ptr<ResultTable>> newGroup;
            newGroup.push_back(table);
            groups.insert({root, newGroup});
        }
    }

    return groups;
}

std::vector<std::shared_ptr<ResultTable>> QueryDb::evaluateGroups() {
    auto allGroups = getGroups();
    std::vector<std::shared_ptr<ResultTable>> groupResults;

    for (const auto& item : allGroups) {
        auto group = item.second;
        std::shared_ptr<ResultTable> individualResults;
        sortTables(group);

        if (!group.empty()) {
            individualResults = group.front();
            group.pop_front();
        }

        while (!group.empty()) {
            auto table = group.front();
            group.pop_front();
            if (!table->getColumnsNamesSet().empty()) {
                individualResults = ResultTable::joinTable(individualResults, table);
            }
        }
        groupResults.emplace_back(individualResults);
    }

    return groupResults;
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

    auto resultGroups = evaluateGroups();

    if (selectedSynonyms.empty()) {
        return getBooleanResults(resultGroups);
    }

    auto interestedResults = getMainResultTableFromGroup(resultGroups);

    if (interestedResults == nullptr) {
        throw std::exception();
    }

    // Map attribute references
    mapAttributeReferences(interestedResults);

    // Filter selected columns
    return interestedResults->getInterestedValues(getInterestedColumns());
}

void QueryDb::mapAttributeReferences(std::shared_ptr<ResultTable> interestedResults) {
    for (const auto& item : selectedSynonyms) {
        auto selectClauseItem = item.first;
        if (SelectClause::isAttribute(selectClauseItem)) {
            auto attributeRef = std::get<AttributeReference>(selectClauseItem);
            // E.g r.stmt#, get values of column r
            auto synonymValues = interestedResults->getColumnOrderedValues(attributeRef.getSynonym());
            // synonym values is transformed in place
            mapAttribute(attributeRef, synonymValues, storage);
            interestedResults->insertCol(SelectClause::getString(selectClauseItem), synonymValues);
        }
    }
}

std::shared_ptr<ResultTable>
QueryDb::getMainResultTableFromGroup(std::vector<std::shared_ptr<ResultTable>> &resultGroups) {
    for (auto &group : resultGroups) {
        auto colNames = group->getColumnsNamesSet();
        if (!colNames.empty() && !selectedSynonyms.empty()
            && colNames.count(SelectClause::getSynonym(selectedSynonyms.at(0).first))) {
            return group;
        }
    }
    return nullptr;
}

std::vector<std::string> QueryDb::getInterestedColumns() {
    std::vector<std::string> res;
    for (const auto& i : selectedSynonyms) {
        res.push_back(SelectClause::getString(i.first));
    }
    return res;
}

std::vector<std::string> QueryDb::getBooleanResults(std::vector<std::shared_ptr<ResultTable>> &resultGroups) {
    std::vector<std::string> res;

    for (const auto& group : resultGroups) {
        // Results is not null, has columns but has no rows
        auto isFalse = group != nullptr && !group->getColumnsNamesSet().empty() && group->getNumberOfRows() == 0;
        if (isFalse) {
            res.emplace_back("FALSE");
            return res;
        }
    }

    res.emplace_back("TRUE");
    return res;
}

bool QueryDb::resultTablesHasFalse() {
    for (const auto& i : results) {
        if (i->hasNoResults()) {
            return true;
        }
    }
    return false;
}
