#pragma once
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <deque>
#include <vector>
#include <utility>
#include "ResultTable.h"
#include "UnionFind.h"
#include "query_processing_system/parser/SelectClause.h"
#include "query_processing_system/evaluator/clause_evaluator/StorageReader.h"
#include "AttributeReferenceMap.h"

using ResultGroups = std::unordered_map<std::string, std::deque<std::shared_ptr<ResultTable>>>;

/**
 * Stores the results from evaluating each clause.
 */
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

    std::shared_ptr<ISourceReader> storage;

    std::unordered_map<std::string, int> colCount;

    /**
     * A disjoint set data structure to store the different groups as part of optimisation.
     * Tables that are part of different groups should be evaluated independently so as to avoid
     * doing an unnecessary cartesian product.
     */
    UnionFind unionFind;

    /**
     * Checks if the list of results contains a result table that equates to false. This means that
     * there would be no final results as False and anything equals false. Hence, no need to join any tables
     * and we can exit early.
     * @return
     */
    bool resultTablesHasFalse();

    /**
     * Get the results if the user specifies a Boolean in the select clause.
     */
    std::vector<std::string> getBooleanResults(std::vector<std::shared_ptr<ResultTable>> &resultGroups);

    /**
     * Given a certain column, map it to an attribute reference. Suppose the user specifies "v.varName", the
     * table only contains columns for "v". This function adds an additional column "v.varname" to the table.
     * The values of the column are obtained from the "v" values.
     * @param interestedResults
     */
    void mapAttributeReferences(std::shared_ptr<ResultTable> interestedResults);

    /**
     * Get all the column names in the list of results.
     */
    std::vector<std::string> getInterestedColumns();

    /**
     * Sort the list of results tables such that the table with the least amount of rows come first.
     * This makes joining the table quicker.
     */
    void sortTables(std::deque<std::shared_ptr<ResultTable>> &tables);

    /**
     * After evaluating the different groups, we get a list of results. This methods get the main interested results
     * from the list of results.
     * @param resultGroups The list of results after evaluating each group.
     * @return The interested results based on the select clause item.
     */
    std::shared_ptr<ResultTable> getMainResultTableFromGroup(std::vector<std::shared_ptr<ResultTable>> &resultGroups);

    /**
     * We can end the evaluation early as there is no results to evaluate.
     */
    std::vector<std::string> earlyExit();

    ResultGroups getGroups();

    std::vector<std::shared_ptr<ResultTable>> evaluateGroups();

    int getScore(std::shared_ptr<ResultTable> tableToScore);

 public:
    explicit QueryDb(std::shared_ptr<ISourceReader> storage);

    /**
     * Add a new result.
     * @param toAdd Result to add.
     */
    void addResult(std::shared_ptr<ResultTable> toAdd);

    void setSelectedColumns(std::vector<std::pair<SelectClauseItem, DesignEntity>> selectedCols);

    /**
     * Join the tables that we are interested in to get the final results.
     * @return The final results.
     */
    std::vector<std::string> getInterestedResults();

    void evaluateAllClauses();

    /**
     * Get all the columns present in results.
     */
    std::unordered_set<std::string> getAllColumnsInResults();
};
