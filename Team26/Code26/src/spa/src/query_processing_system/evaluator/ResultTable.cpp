#include "ResultTable.h"
#include <map>
#include <iostream>
#include <algorithm>

ResultTable::ResultTable() = default;

ResultTable::ResultTable(TableRow columnNames) {
    for (int i = 0; i < columnNames.size(); i++) {
        columnNameMap.insert({i, columnNames.at(i)});
    }
}

ResultTable::ResultTable(std::string columnName) {
    columnNameMap.insert({0, columnName});
}

std::shared_ptr<ResultTable>
ResultTable::createSingleColumnTable(std::string column1, std::unordered_set<std::string> values) {
    auto res = std::make_shared<ResultTable>(column1);
    for (auto i : values) {
        res->insertRow({i});
    }
    return res;
}

std::shared_ptr<ResultTable>
ResultTable::createDoubleColumnTable(std::string column1, std::unordered_set<std::string> values1,
                                     std::string column2, std::unordered_set<std::string> values2) {
    auto colNames = TableRow {column1, column2};
    auto res = std::make_shared<ResultTable>(colNames);
    for (auto i : values1) {
        for (auto j : values2) {
            res->insertRow({i, j});
        }
    }
    return res;
}

std::shared_ptr<ResultTable>
ResultTable::createTableFromMap(std::unordered_map<std::string, std::unordered_set<std::string>> map,
                                std::string keysCol, std::string valuesCol) {
    auto colNames = TableRow {keysCol, valuesCol};
    auto res = std::make_shared<ResultTable>(colNames);
    for (auto const& [k, v] : map) {
        for (auto item : v) {
            res->insertRow({k, item});
        }
    }
    return res;
}

std::shared_ptr<ResultTable>
ResultTable::joinTable(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2) {
    auto commonCols = table1->hasMatchingColumns(table2->getColumnsNamesSet());
    if (commonCols.empty()) {
        return joinNoColumns(table1, table2);
    } else {
        return joinOnColumns(table1, table2, commonCols);
    }
}

std::shared_ptr<ResultTable>
ResultTable::joinNoColumns(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2) {
    auto newTableColumns = ResultTable::getVectorUnion(table1->getColumnsNames(), table2->getColumnsNames());
    auto res = std::make_shared<ResultTable>(newTableColumns);
    for (int i = 0; i < table1->getNumberOfRows(); i++) {
        for (int j = 0; j < table2->getNumberOfRows(); j++) {
            TableRow row;
            auto table1Row = table1->getRow(i);
            auto table2Row = table2->getRow(j);
            row.insert(row.end(), table1Row.begin(), table1Row.end());
            row.insert(row.end(), table2Row.begin(), table2Row.end());
            res->insertRow(row);
        }
    }
    return res;
}

std::shared_ptr<ResultTable> ResultTable::joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                       std::shared_ptr<ResultTable> table2,
                                                       std::vector<std::string> commonColumns) {
    auto col1 = table1->getColumnNumbers(commonColumns);
    auto col2 = table2->getColumnNumbers(commonColumns);
    if (col1.size() > 0 && col2.size() > 0) {
        return joinOnColumns(table1, table2, col1, col2);
    } else {
        throw std::exception();
    }
}

std::shared_ptr<ResultTable> ResultTable::joinOnColumns(std::shared_ptr<ResultTable> table1,
                                                       std::shared_ptr<ResultTable> table2,
                                                       std::vector<int> column1,
                                                       std::vector<int> column2) {
    auto newTableColumns = ResultTable::getVectorUnion(table1->getColumnsNames(), table2->getColumnsNames());
    auto res = std::make_shared<ResultTable>(newTableColumns);
    if (table2->getNumberOfRows() == 0) {
        // Joining with an empty table
        return res;
    }

    std::unordered_multimap<std::vector<std::string >, int, VectorHash> hashmap;
    for (int i = 0; i < table2->getNumberOfRows(); i++) {
        hashmap.insert({table2->getValuesAt(i, column2), i});
    }

    for (int i = 0; i < table1->getNumberOfRows(); i++) {
        auto range = hashmap.equal_range(table1->getValuesAt(i, column1));
        for (auto it = range.first; it != range.second; it++) {
            TableRow row;
            auto table1Row = table1->getRow(i);
            auto table2Row = table2->getRow(it->second);
            row.insert(row.end(), table1Row.begin(), table1Row.end());
            for (int j = 0; j < table2Row.size(); j++) {
                if (std::find(column2.begin(), column2.end(), j) == column2.end()) {
                    row.push_back(table2Row.at(j));
                }
            }
            res->insertRow(row);
        }
    }
    return res;
}

int ResultTable::getColumnNumber(std::string colName) const {
    for (auto const& [k, v] : columnNameMap) {
        if (colName == v) {
            return k;
        }
    }
    return -1;
}
std::vector<int> ResultTable::getColumnNumbers(std::vector<std::string> colName) const {
    std::vector<int> res(colName.size());
    for (auto const& [k, v] : columnNameMap) {
        auto it = std::find(colName.begin(), colName.end(), v);
        if (it != colName.end()) {
            res.at(it - colName.begin()) = k;
        }
    }
    return res;
}

void ResultTable::insertRow(TableRow row) {
    if (row.size() != columnNameMap.size()) {
        std::cout << row.size() << "\n";
        std::cout << "Adding row failed\n";
        throw std::exception();
    }
    relations.push_back(row);
}

TableRow ResultTable::getColumnsNames() const {
    TableRow res(columnNameMap.size());
    for (auto const& [k, v] : columnNameMap) {
        res.at(k) = v;
    }
    return res;
}

std::unordered_set<std::string> ResultTable::getColumnsNamesSet() const {
    std::unordered_set<std::string> res;
    for (auto const& [k, v] : columnNameMap) {
        res.insert(v);
    }
    return res;
}

std::unordered_set<std::string> ResultTable::getColumnValues(std::string colName) {
    int colInt = getColumnNumber(colName);
    std::unordered_set<std::string> res;
    for (int i = 0; i < relations.size(); i++) {
        res.insert(getValueAt(i, colInt));
    }
    return res;
}

TableRow ResultTable::hasMatchingColumns(std::unordered_set<std::string> columnNamesToMatch) {
    std::vector<std::string> res;
    for (auto const& [k, v] : columnNameMap) {
        if (columnNamesToMatch.count(v)) {
            res.push_back(v);
        }
    }
    return res;
}

TableRow ResultTable::getRow(int rowNumber) const {
    return relations.at(rowNumber);
}

std::string ResultTable::getValueAt(int rowNumber, int columnNumber) const {
    return relations.at(rowNumber).at(columnNumber);
}

TableRow ResultTable::getValuesAt(int rowNumber, std::vector<int> columnNumbers) const {
    auto row = relations.at(rowNumber);
    std::vector<std::string> res;
    for (auto col : columnNumbers) {
        res.push_back(row.at(col));
    }
    return res;
}

TableRow ResultTable::getInterestedValues(std::vector<std::string> interestedColumns) const {
    auto colNum = getColumnNumbers(interestedColumns);
    std::unordered_set<std::string> values;
    for (int i = 0; i < relations.size(); i++) {
        auto rowValue = getValuesAt(i, colNum);
        std::string s;
        std::for_each(rowValue.begin(), rowValue.end(), [&](const std::string &piece) { s += (" " + piece); });
        s.erase(0, 1);
        values.insert(s);
    }
    TableRow res;
    res.insert(res.end(), values.begin(), values.end());
    return res;
}

int ResultTable::getNumberOfRows() const {
    return relations.size();
}

TableRow ResultTable::getVectorUnion(TableRow vector1, TableRow vector2) {
    for (auto item : vector2) {
        if (std::find(vector1.begin(), vector1.end(), item) == vector1.end()) {
            vector1.push_back(item);
        }
    }
    return vector1;
}

void ResultTable::setNoResults() {
    noResults = true;
}

bool ResultTable::hasNoResults() {
    return noResults;
}
