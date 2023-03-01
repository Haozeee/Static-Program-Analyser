#include "QueryDb.h"
#include <memory>
QueryDb::QueryDb() {}

void QueryDb::addResult(std::shared_ptr<ResultTable> toAdd) {
    results.push_back(toAdd);
}

void QueryDb::addSelectedColumn(std::string col) {
    selectedSynonyms.push_back(col);
}

std::vector<std::string> QueryDb::getInterestedResults() {
    std::vector<std::string> res;
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

    // Filter selected columns
    return interestedResults->getInterestedValues(selectedSynonyms);
}

bool QueryDb::resultTablesHasFalse() {
    for (auto i : results) {
        if (i->hasNoResults()) {
            return true;
        }
    }
    return false;
}
