#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>

using ResultMap = std::unordered_map<std::string, std::unordered_set<std::string>>;

class ClauseResult {
 private:
    ResultMap results;
    /**
     * Indicates if the clause has any results.
     */
    bool noResults = false;

 public:
    void addNewItem(std::string key, std::unordered_set<std::string> values);

    ResultMap getResults();

    void setNoResults();

    bool hasNoResults();
};
