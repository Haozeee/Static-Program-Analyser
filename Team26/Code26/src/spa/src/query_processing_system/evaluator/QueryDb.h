#pragma once
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <deque>
#include "ResultTable.h"

class QueryDb {
 private:
    /**
     * Store the synonyms that the user has selected in the query.
     */
    std::vector<std::string> selectedSynonyms;

    /**
     * Store a list of result tables. The result tables can come from the select clause or
     * evaluating a such that and pattern clause. The reason we store it as a list of table, rather
     * than joining it whenever we have a new table is that some tables may not be irrelevant to the final
     * results. Hence, joining them would be a waste of resources.
     */
    std::deque<std::shared_ptr<ResultTable>> results;

    /**
     * Checks if the list of results contains a result table that equates to false. This means that
     * there would be no final results as False and anything equals false. Hence, no need to join any tables
     * and we can exit early.
     * @return
     */
    bool resultTablesHasFalse();

    std::vector<std::string> getBooleanResults(std::shared_ptr<ResultTable> interestedResults);

 public:
    QueryDb();

    void addResult(std::shared_ptr<ResultTable> toAdd);

    void addSelectedColumn(std::string col);

    /**
     * Join the tables that we are interested in to get the final results.
     * @return The final results.
     */
    std::vector<std::string> getInterestedResults();
};
