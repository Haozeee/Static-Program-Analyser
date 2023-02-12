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

    while (!results.empty()) {
        bool hasJoin = false;
        for (int i = 0 ; i < results.size(); i++) {
            auto match = results.at(i)->hasMatchingColumns(interestedColumns);
            if (!match.empty()) {
                interestedResults = ResultTable::joinOnColumn(interestedResults, results.at(i), match);
                hasJoin = true;
                results.erase(results.begin() + i);
                auto cols = interestedResults->getColumnsNames();
                interestedColumns.insert(cols.begin(), cols.end());
            }
        }
        std::cout << "1\n";
        if (!hasJoin) {
            break;
        }
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    res.insert({selectedSynonyms, interestedResults->getColumnValues(selectedSynonyms)});
    return res;
}
