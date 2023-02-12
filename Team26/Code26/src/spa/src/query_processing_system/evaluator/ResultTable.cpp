#include "ResultTable.h"
#include <map>
#include <iostream>

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

std::shared_ptr<ResultTable> ResultTable::joinOnColumn(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2, std::string commonColumn) {
    auto col1 = table1->getColumnNumber(commonColumn);
    auto col2 = table2->getColumnNumber(commonColumn);
    if (col1 != -1 and col2 != -1) {
        return joinOnColumn(table1, table2, col1, col2);
    } else {
        throw std::exception();
    }
}

std::shared_ptr<ResultTable> ResultTable::joinOnColumn(std::shared_ptr<ResultTable> table1, std::shared_ptr<ResultTable> table2, int column1, int column2) {
    std::unordered_multimap<std::string, int> hashmap;
    for (int i = 0; i < table2->getNumberOfRows(); i++) {
        hashmap.insert({table2->getValueAt(i, column2), i});
    }
    auto newTableColumns = ResultTable::getVectorUnion(table1->getColumnsNames(), table2->getColumnsNames());
    auto res = std::make_shared<ResultTable>(newTableColumns);
    for (int i = 0; i < table1->getNumberOfRows(); i++) {
        auto range = hashmap.equal_range(table1->getValueAt(i, column1));
        for (auto it = range.first; it != range.second; it++) {
            TableRow row;
            auto table1Row = table1->getRow(i);
            auto table2Row = table2->getRow(it->second);
            row.insert(row.end(), table1Row.begin(), table1Row.end());
            for (int j = 0; j < table2Row.size(); j++) {
                if (j != column2) {
                    row.push_back(table2Row.at(j));
                }
            }
            std::cout << row.size() << " size\n";
            res->insertRow(row);
        }
    }
    return res;
}

int ResultTable::getColumnNumber(std::string colName) const {
    for (auto const& [k, v] : columnNameMap) {
        if (v == colName) {
            return k;
        }
    }
    return -1;
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
    TableRow res;
    for (auto const& [k, v] : columnNameMap) {
        res.push_back(v);
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

std::string ResultTable::hasMatchingColumns(std::unordered_set<std::string> columnNames) {
    for (auto const& [k, v] : columnNameMap) {
        if (columnNames.count(v)) {
            return v;
        }
    }
    return "";
}

TableRow ResultTable::getRow(int rowNumber) const {
    return relations.at(rowNumber);
}

std::string ResultTable::getValueAt(int rowNumber, int columnNumber) const {
    return relations.at(rowNumber).at(columnNumber);
}

int ResultTable::getNumberOfRows() const {
    return relations.size();
}

TableRow ResultTable::getVectorUnion(TableRow vector1, TableRow vector2) {
    for (auto item : vector2) {
        if (std::find(vector1.begin(), vector1.end(), item) != vector1.end()) {
            vector2.push_back(item);
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
