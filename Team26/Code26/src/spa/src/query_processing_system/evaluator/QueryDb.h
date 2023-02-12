#pragma once
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "ResultTable.h"

class QueryDb {
 private:
    std::string selectedSynonyms;

    std::vector<std::shared_ptr<ResultTable>> results;

    std::unordered_set<std::string> interestedColumns;

 public:
    QueryDb();

    void addResult(std::shared_ptr<ResultTable> toAdd);

    void setSelectedColumn(std::string col);

    std::unordered_map<std::string, std::unordered_set<std::string>> getInterestedResults();
};
