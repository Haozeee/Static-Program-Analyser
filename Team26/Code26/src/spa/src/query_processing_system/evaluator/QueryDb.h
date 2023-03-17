#pragma once
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <deque>
#include <vector>
#include <utility>
#include "ResultTable.h"
#include "AttributeReferenceMap.h"
#include "query_processing_system/parser/SelectClause.h"
#include "program_knowledge_base/StorageUtil.h"
#include "program_knowledge_base/StorageManager.h"

class QueryDb {
 private:
    /**
     * Store the synonyms that the user has selected in the query.
     */
    std::vector<std::pair<SelectClauseItem, DesignEntity>> selectedSynonyms;

    /**
     * Store a list of result tables. The result tables can come from the select clause or
     * evaluating a such that and pattern clause. The reason we store it as a list of table, rather
     * than joining it whenever we have a new table is that some tables may not be irrelevant to the final
     * results. Hence, joining them prematurely would be a wasteful.
     */
    std::deque<std::shared_ptr<ResultTable>> results;

    std::shared_ptr<ReadStorage> storage;

    /**
     * Checks if the list of results contains a result table that equates to false. This means that
     * there would be no final results as False and anything equals false. Hence, no need to join any tables
     * and we can exit early.
     * @return
     */
    bool resultTablesHasFalse();

    std::vector<std::string> getBooleanResults(std::shared_ptr<ResultTable> interestedResults);

    void mapAttributeReferences(std::shared_ptr<ResultTable> interestedResults);

    /**
     * Get all the column names in the list of results.
     */
    std::vector<std::string> getInterestedColumns();

    /**
     * After evaluating the clauses, some of the selected values may not appear as a column in the results.
     */
    void fillMissingTables();

    /**
     * Get all the columns present in results.
     */
    std::unordered_set<std::string> getAllColumnsInResults();

    /**
     * Sort the list of results tables such that the table with the least amount of rows come first.
     * This makes joining the table quicker.
     */
    void sortResultTables();

 public:
    explicit QueryDb(std::shared_ptr<ReadStorage> storage);

    void addResult(std::shared_ptr<ResultTable> toAdd);

    void addSelectedColumn(const SelectClauseItem& selectClauseItem, DesignEntity designEntity);

    /**
     * Join the tables that we are interested in to get the final results.
     * @return The final results.
     */
    std::vector<std::string> getInterestedResults();
};
