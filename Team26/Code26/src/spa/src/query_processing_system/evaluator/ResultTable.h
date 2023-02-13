#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>

using TableRow = std::vector<std::string>;

struct VectorHash {
    size_t operator()(const std::vector<std::string>& v) const {
        std::hash<std::string> hasher;
        size_t seed = v.size();
        for (auto i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

class ResultTable {
 private:
    std::unordered_map<int, std::string> columnNameMap;

    std::vector<TableRow> relations;

    /**
     * If true, when this table is joined with any other table,
     * an empty table is returned.
     */
    bool noResults = false;

    static std::shared_ptr<ResultTable> joinOnColumns(std::shared_ptr<ResultTable> table1,
                                               std::shared_ptr<ResultTable> table2,
                                               std::vector<int> column1,
                                               std::vector<int> column2);
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
    static std::shared_ptr<ResultTable> joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                      std::shared_ptr<ResultTable> table2,
                                                      std::vector<std::string> commonColumns);

    /**
     * Given a set of columnNames, check if this table has any column
     * in the given set.
     * @return The similar column name. If no matching column name, return "".
     */
    std::vector<std::string> hasMatchingColumns(std::unordered_set<std::string> columnNames);

    void insertRow(TableRow row);

    TableRow getRow(int rowNumber) const;

    std::string getValueAt(int rowNumber, int columnNumber) const;

    std::vector<std::string> getValuesAt(int rowNumber, std::vector<int> columnNumbers) const;

    /**
     * Returns the column numbers of the column with name colName.
     * @return The column number, -1 if the column does not exist.
     */
    std::vector<int> getColumnNumbers(std::vector<std::string> colName) const;

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
