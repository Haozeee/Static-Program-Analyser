#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_set>
#include <unordered_map>

using TableRow = std::vector<std::string>;

/**
 * Hash function to hash a vector.
 * Obtained from:
 * https://stackoverflow.com/questions/29855908/c-unordered-set-of-vectors
 */
struct VectorHash {
    size_t operator()(const std::vector<std::string>& v) const {
        std::hash<std::string> hasher;
        size_t seed = v.size();
        for (auto i : v) {
            // You can read more about why these numbers are used in the link in the function description.
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

/**
 * Represents a relational table to store the results of a clause.
 */
class ResultTable {
 private:
    /**
     * Maps the column number to a column name.
     */
    std::unordered_map<int, std::string> columnNameMap;

    /**
     * A vector in which each elements represent a row in the relational table.
     */
    std::vector<TableRow> relations;

    /**
     * If true, when this table is joined with any other table,
     * an empty table is returned.
     */
    bool noResults = false;

    /**
     * Join table 1 and table 2.
     * @param table1
     * @param table2
     * @param column1
     * @param column2
     * @return
     */
    static std::shared_ptr<ResultTable> joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                      std::shared_ptr<ResultTable> table2,
                                                      std::vector<int> &column1, std::vector<int> &column2);

    /**
     * Suppose common columns are a list of columns that are present in table1 and table2.
     * This function joins the two table on the common columns and return the newly joined table.
     * Suppose commonColumns = ["A", "B"]. This function joins table1 and table2 on
     * table1.A = table2.A and table1.B = table2.B.
     * If there are cols in common cols that are not in both the tables, an exception is thrown.
     */
    static std::shared_ptr<ResultTable> joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                      std::shared_ptr<ResultTable> table2,
                                                      std::vector<std::string> &commonColumns);

    /**
     * Join 2 tables that have no common columns.
     */
    static std::shared_ptr<ResultTable> joinNoCommonColumns(std::shared_ptr<ResultTable> table1,
                                                            std::shared_ptr<ResultTable> table2);
    /**
     * Union 2 vectors.
     */
    static TableRow getVectorUnion(TableRow vector1, TableRow vector2);

    static TableRow joinTableHelper(TableRow table1Row, TableRow table2Row, std::vector<int> &column2);

 public:
    /**
     * Creates an empty table.
     */
    ResultTable();

    /**
     * Create a table with one column.
     * @param columnName
     */
    explicit ResultTable(std::string columnName);

    /**
     * Create a table with multiple columns. Ideally, this should be private but std::make shared
     * requires that the constructor be public. Use the factory method to construct the table.
     */
    explicit ResultTable(TableRow columnNames);

    /**
     * Create a table with one column.
     * @param column1 The name of the column.
     * @param values The values of the column.
     */
    static std::shared_ptr<ResultTable>
    createSingleColumnTable(std::string column1, std::unordered_set<std::string> values);

    /**
     * Given an unordered map, create a 2 column relational table with each (key, value) pair to
     * be in the table.
     */
    static std::shared_ptr<ResultTable>
    createTableFromMap(std::unordered_map<std::string, std::unordered_set<std::string>> map,
                       std::string keysCol, std::string valuesCol);

    /**
     * Join table1 and table2. If there are no common columns to join, do a cartesian product between the
     * 2 tables.
     */
    static std::shared_ptr<ResultTable> joinTable(std::shared_ptr<ResultTable> table1,
                                                  std::shared_ptr<ResultTable> table2);

    /**
     * Given a set of columnNamesToMatch, check if this table has any of these columns in it.
     * @return A vector containing the names of the matching columns. If there are no matching columns,
     * an empty vector is returned.
     */
    TableRow hasMatchingColumns(std::unordered_set<std::string> columnNamesToMatch);

    /**
     * Insert a row into this table. An exception is thrown if the row added does not match the dimensions
     * of the table.
     * @param row The row to be added.
     */
    void insertRow(TableRow row);

    /**
     * Insert a column into this table. An exception is thrown if the column added does not match the dimensions
     * of the table.
     * @param colName The name of the new column.
     * @param colValues The values of the column to be added.
     */
    void insertCol(std::string colName, std::vector<std::string> colValues);

    /**
     * Get the entire row at rowNumber.
     */
    TableRow getRow(int rowNumber) const;

    /**
     * Given a rowNumber and columnNumber, get the value at that position.
     * @param rowNumber The row number.
     * @param columnNumber the column number.
     * @return The value at that row number and column number.
     */
    std::string getValueAt(int rowNumber, int columnNumber) const;

    /**
     * Given a row number i and a list of interested column numbers,
     * return the ith row containing only the values of the interested columns.
     */
    TableRow getValuesAt(int rowNumber, std::vector<int> &columnNumbers) const;

    /**
     * Given a list of interested columns, return the values of only the interested columns
     * in the form of a vector of strings.
     * For each row, combine the results together by concatenating the entire row into a string.
     * @param interestedColumns The columns of the table that we are interested in.
     * @return The interested results in the form of a vector of strings. The results should be distinct.
     */
    TableRow getInterestedValues(std::vector<std::string> interestedColumns) const;

    /**
     * Given a column name, get all the values under this column. This removes any duplicates
     * in the column. The results are returned as a set, hence the ordering is undefined.
     */
    std::unordered_set<std::string> getColumnValues(std::string colName);

    /**
     * Given a column name, get all the values under this column. Duplicated are
     * not removed from the results. The results are returned as a vector, and the order
     * of the table is preserved in the results,
     */
    TableRow getColumnOrderedValues(std::string colName);

    /**
     * For each column name in colName, get the corresponding column number.
     * The order of the results is in the order of colName.
     * If the column name does not exist, the column number will be 0.
     */
    std::vector<int> getColumnNumbers(std::vector<std::string> &colName) const;

    /**
     * Returns the column number of the column with name colName.
     * @return The column number, -1 if the column does not exist.
     */
    int getColumnNumber(const std::string& colName) const;

    /**
     * Get number of rows of this table.
     */
    int getNumberOfRows() const;

    /**
     * Get the column names of this table. The order of the results
     * matches the way the columns of the table are ordered.
     */
    TableRow getColumnsNames() const;

    /**
     * Get the column names of this table. The order of the column
     * names does not matter.
     */
    std::unordered_set<std::string> getColumnsNamesSet() const;

    bool hasNoResults();

    void setNoResults();
};
