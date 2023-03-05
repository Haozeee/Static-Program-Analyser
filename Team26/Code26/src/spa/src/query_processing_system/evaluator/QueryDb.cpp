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

    // Filter selected columns
    return interestedResults->getInterestedValues(selectedSynonyms);
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
