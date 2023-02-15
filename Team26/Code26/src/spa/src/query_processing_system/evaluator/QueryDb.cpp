#include "QueryDb.h"
#include <memory>
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
    int i = 0;
    while (!results.empty() && i < results.size()) {
        auto table = results.front();
        results.pop_front();
        auto match = table->hasMatchingColumns(interestedColumns);
        if (!match.empty()) {
            interestedResults = ResultTable::joinOnColumns(interestedResults, table, match);
            auto cols = interestedResults->getColumnsNames();
            interestedColumns.insert(cols.begin(), cols.end());
            i = 0;
        } else {
            results.push_back(table);
            i++;
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
