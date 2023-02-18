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

    auto interestedResults = results.front();
    results.pop_front();

    while (!results.empty()) {
        auto table = results.front();
        results.pop_front();
        if (!table->getColumnsNamesSet().empty()) {
            interestedResults = ResultTable::joinTable(interestedResults, table);
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
