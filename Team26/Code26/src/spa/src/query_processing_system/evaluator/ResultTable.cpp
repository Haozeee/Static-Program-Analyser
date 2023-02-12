#include "ResultTable.h"
#include <map>
#include <set>

ResultTable::ResultTable(TableRow columnNames) {
    for (int i = 0; i < columnNames.size(); i++) {
        columnNameMap.insert({i, columnNames.at(i)});
    }
}

ResultTable::ResultTable(std::string columnName) {
    columnNameMap.insert({0, columnName});
}

void ResultTable::join(const ResultTable &table) {
    auto commonColumns = ResultTable::getVectorIntersection(headers, table.getHeaders());
    if (commonColumns.size() > 0) {
        joinOnColumn(table, commonColumns);
    } else {
        joinNoColumn(table);
    }
}

ResultTable ResultTable::joinNoColumn(ResultTable &table1, const ResultTable &table2) {
    auto newTableColumns = ResultTable::getVectorUnion(table1.getColumnsNames(), table2.getColumnsNames());
    ResultTable res = ResultTable(newTableColumns);
    for (int i = 0; i < table1.getNumberOfRows(); i++) {
        for (int j = 0; j < table2.getNumberOfRows(); j++) {
            TableRow row;
            row.insert(row.end(), table1.getRow(i).begin(), table1.getRow(i).end());
            row.insert(row.end(), table2.getRow(j).begin(), table2.getRow(j).end());
            res.insertRow(row);
        }
    }
    return res;
}

ResultTable ResultTable::joinOnColumn(ResultTable &table1, const ResultTable &table2, int column1, int column2) {
    std::unordered_multimap<std::string, int> hashmap;
    for (int i = 0; i < table2.getNumberOfRows(); i++) {
        hashmap.insert({table2.getValueAt(i, column2), i});
    }
    auto newTableColumns = ResultTable::getVectorUnion(table1.getColumnsNames(), table2.getColumnsNames());
    ResultTable res = ResultTable(newTableColumns);
    for (int i = 0; i < table1.getNumberOfRows(); i++) {
        auto range = hashmap.equal_range(table1.getValueAt(i, column1));
        for (auto it = range.first; it != range.second; i++) {
            TableRow row;
            row.insert(row.end(), table1.getRow(i).begin(), table1.getRow(i).end());
            row.insert(row.end(), table2.getRow(it->second).begin(), table2.getRow(it->second).end());
            res.insertRow(row);
        }
    }
    return res;
}

ResultTable ResultTable::joinAllColumn(ResultTable &table1, const ResultTable &table2) {
    std::set<std::vector<int>>
    ResultTable res = ResultTable(table1.getColumnsNames());
}

void ResultTable::insertRow(TableRow row) {
    if (row.size() != columnNameMap.size()) {
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

TableRow ResultTable::getHeaders() const {
    return headers;
}

TableRow ResultTable::getRow(int rowNumber) {
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