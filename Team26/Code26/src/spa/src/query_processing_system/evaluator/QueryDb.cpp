#include "QueryDb.h"
#include <memory>
#include <iostream>
QueryDb::QueryDb() {}

void QueryDb::addResult(std::shared_ptr<ResultTable> toAdd) {
    results.push_back(toAdd);
}

void QueryDb::setSelectedColumn(std::string col) {
    selectedSynonyms = col;
    interestedColumns.insert(col);
}

std::unordered_map<std::string, std::unordered_set<std::string>> QueryDb::getInterestedResults() {
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    if (resultTablesHasFalse()) {
        return res;
    }
    auto interestedResults = std::make_shared<ResultTable>();
    // Get base results
    for (int i = 0 ; i < results.size(); i++) {
        auto match = results.at(i)->hasMatchingColumns(interestedColumns);
        if (!match.empty()) {
            interestedResults = results.at(i);
            results.erase(results.begin() + i);
            break;
        }
    }

    // Keep joining the interested tables until there are no more interested tables to join
    while (!results.empty()) {
        bool hasJoin = false;
        for (int i = 0 ; i < results.size(); i++) {
            auto match = results.at(i)->hasMatchingColumns(interestedColumns);
            if (!match.empty()) {
                interestedResults = ResultTable::joinOnColumns(interestedResults, results.at(i), match);
                hasJoin = true;
                results.erase(results.begin() + i);
                auto cols = interestedResults->getColumnsNames();
                interestedColumns.insert(cols.begin(), cols.end());
            }
        }
        if (!hasJoin) {
            break;
        }
    }
    // Store the result into an unordered map
    res.insert({selectedSynonyms, interestedResults->getColumnValues(selectedSynonyms)});
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
