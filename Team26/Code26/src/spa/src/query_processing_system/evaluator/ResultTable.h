#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using TableRow = std::vector<std::string>;

class ResultTable {
 private:
    std::unordered_map<int, std::string> columnNameMap;

    std::vector<TableRow> relations;
    /**
     * Join table1 and table2 on table1.column1 = table2.column2
     * @param table1
     * @param table2
     * @param column1
     * @param column2
     */
    static ResultTable joinOnColumn(ResultTable &table1, const ResultTable &table2, int column1, int column2);

    /**
     * To be used only when all columns in table2 are columns in table1.
     */
    static ResultTable joinAllColumn(ResultTable &table1, const ResultTable &table2);

    /**
     * Join two tables that have no common columns. Does a cartesian product between the two table.
     */
    static ResultTable joinNoColumn(ResultTable &table1, const ResultTable &table2);

    void joinNoColumn(const ResultTable &table);

    static TableRow getVectorIntersection(TableRow vector1, TableRow vector2);

    static TableRow getVectorUnion(TableRow vector1, TableRow vector2);


 public:
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

    void join(const ResultTable &table);

    void insertRow(TableRow row);

    TableRow getHeaders() const;

    TableRow getRow(int rowNumber) const;

    std::string getValueAt(int rowNumber, int columnName) const;

    int getNumberOfRows() const;

    TableRow getColumnsNames() const;
};
