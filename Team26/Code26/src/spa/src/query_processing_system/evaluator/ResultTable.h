#pragma once
#include <vector>
#include <string>
#include <memory>
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
                                                      std::vector<int> column1, std::vector<int> column2);

    /**
     * Suppose common columns are a list of columns that are present in table1 and table2.
     * This function joins the two table on the common columns and return the newly joined table.
     * Suppose commonColumns = ["A", "B"]. This function joins table1 and table2 on
     * table1.A = table2.A and table1.B = table2.B.
     */
    static std::shared_ptr<ResultTable> joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                      std::shared_ptr<ResultTable> table2,
                                                      std::vector<std::string> commonColumns);

    /**
     * Join 2 tables that have no common columns.
     */
    static std::shared_ptr<ResultTable> joinNoColumns(std::shared_ptr<ResultTable> table1,
                                                      std::shared_ptr<ResultTable> table2);
    /**
     * Union 2 vectors.
     */
    static TableRow getVectorUnion(TableRow vector1, TableRow vector2);

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
     * Create a table with multiple column.
     * @param columnNames
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
     * Creates a table with two columns by doing a cartesian product of the two unordered sets.
     * @param column1 The name of the first column.
     * @param column2 the name of the second column.
     */
    static std::shared_ptr<ResultTable>
    createDoubleColumnTable(std::string column1, std::unordered_set<std::string> values1,
                            std::string column2, std::unordered_set<std::string> values2);

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
     * @return A set containing the names of the matching columns. If there are no matching columns,
     * an empty set is returned.
     */
    std::vector<std::string> hasMatchingColumns(std::unordered_set<std::string> columnNamesToMatch);

    /**
     * Insert a row into this table. An exception is thrown if the row added does not match the dimensions
     * of the table.
     * @param row The row to be added.
     */
    void insertRow(TableRow row);

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
     * return the ith row containing only the values in the interested columns.
     */
    std::vector<std::string> getValuesAt(int rowNumber, std::vector<int> columnNumbers) const;

    /**
     * Given a column name, get all the values under this column.
     */
    std::unordered_set<std::string> getColumnValues(std::string colName);

    /**
     * Returns the column numbers of the columns that exists in the vector colName.
     */
    std::vector<int> getColumnNumbers(std::vector<std::string> colName) const;

    /**
     * Returns the column number of the column with name colName.
     * @return The column number, -1 if the column does not exist.
     */
    int getColumnNumber(std::string colName) const;

    /**
     * Get number of rows of this table.
     */
    int getNumberOfRows() const;

    /**
     * Get the column names of this table. The order of the column
     * names matter.
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
