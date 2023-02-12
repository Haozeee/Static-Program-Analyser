#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>

using TableRow = std::vector<std::string>;

class ResultTable {
 private:
    std::unordered_map<int, std::string> columnNameMap;

    std::vector<TableRow> relations;

    /**
     * If true, when this table is joined with any other table,
     * an empty table is returned.
     */
    bool noResults = false;

    static std::shared_ptr<ResultTable> joinOnColumn(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2, int column1, int column2);

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
    ResultTable(std::string columnName);

    /**
     * Create a table with multiple column.
     * @param columnNames
     */
    ResultTable(TableRow columnNames);

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
     * Join on table1.commonColumn = table2.commonColumn
     */
    static std::shared_ptr<ResultTable> joinOnColumn(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2, std::string commonColumn);

    /**
     * Given a set of columnNames, check if this table has any column
     * in the given set.
     * @return The similar column name.
     */
    std::string hasMatchingColumns(std::unordered_set<std::string> columnNames);

    void insertRow(TableRow row);

    TableRow getRow(int rowNumber) const;

    std::string getValueAt(int rowNumber, int columnName) const;

    /**
     * Returns the column number of the column with name colName.
     * @return The column number, -1 if the column does not exist.
     */
    int getColumnNumber(std::string colName) const;

    /**
     * Given a column name, get all the values of this columne.
     */
    std::unordered_set<std::string> getColumnValues(std::string colName);

    int getNumberOfRows() const;

    TableRow getColumnsNames() const;

    bool hasNoResults();

    void setNoResults();
};
