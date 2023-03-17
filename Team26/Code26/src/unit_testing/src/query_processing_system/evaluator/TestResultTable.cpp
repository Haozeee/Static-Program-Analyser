#include "catch.hpp"
#include "query_processing_system/evaluator/ResultTable.h"

// Create single tables to used for testing
std::unordered_set<std::string> tableAItems {"a", "b", "c"};
std::string tableACol = "col1";
auto tableA = ResultTable::createSingleColumnTable(tableACol, tableAItems);

// Create double columns table to be used for testing
std::unordered_map<std::string, std::unordered_set<std::string>> tableBItems {
        {"a", {"c", "d"}},
        {"b", {"c", "d"}}
};
std::unordered_set<std::string> tableBItems1 {"a", "b"};
std::unordered_set<std::string> tableBItems2 {"c", "d"};
std::string tableBCol1 = "col1";
std::string tableBCol2 = "col2";
auto tableB = ResultTable::createTableFromMap(tableBItems, tableBCol1, tableBCol2);

// Create double columns table to be used for testing
std::unordered_set<std::string> tableCItems1 {"b"};
std::unordered_set<std::string> tableCItems2 {"c", "d"};
std::unordered_map<std::string, std::unordered_set<std::string>> tableCItems {
        {"b", {"c", "d"}}
};
auto tableC = ResultTable::createTableFromMap(tableCItems, tableBCol1, tableBCol2);

std::unordered_map<std::string, std::unordered_set<std::string>> tableDItems {
        {"c", {"b"}},
        {"d", {"b"}}
};
auto tableD = ResultTable::createTableFromMap(tableDItems, tableBCol2, tableBCol1);

std::unordered_set<std::string> vectorToSet(std::vector<std::string> v) {
    std::unordered_set<std::string> res;
    for (auto i : v) {
        res.insert(i);
    }
    return res;
}

TEST_CASE("Constructing Table From Map") {
    std::unordered_map<std::string, std::unordered_set<std::string>> map {
            {"1", {"2", "3"}},
            {"9", {"12"}}
    };
    auto mapTable = ResultTable::createTableFromMap(map, tableBCol1, tableBCol2);
    std::vector<std::string> row1 = {"1", "2"};
    std::vector<std::string> row2 = {"1", "3"};
    std::vector<std::string> row3 = {"9", "12"};
    REQUIRE(mapTable->getRow(0) == row1);
    REQUIRE(mapTable->getRow(1) == row2);
    REQUIRE(mapTable->getRow(2) == row3);

    // Creating a double column table with same name
    map = {
            {"1", {"1"}},
            {"2", {"2"}}
    };
    mapTable = ResultTable::createTableFromMap(map, tableBCol1, tableBCol1);
    REQUIRE(mapTable->getColumnsNamesSet().size() == 1);
    std::unordered_set<std::string> res {"1", "2"};
    REQUIRE(mapTable->getColumnValues(tableBCol1) == res);

    // Create double column table with empty map
    map = {};
    mapTable = ResultTable::createTableFromMap(map, tableBCol1, tableBCol2);
    REQUIRE(mapTable->getColumnsNamesSet().size() == 2);
    REQUIRE(mapTable->getNumberOfRows() == 0);
}

TEST_CASE("Double Table") {
    // Check correct dimensions of table
    auto tableBColNames = tableB->getColumnsNames();
    REQUIRE(tableBColNames.size() == 2);
    REQUIRE(tableBColNames[0] == tableBCol1);
    REQUIRE(tableBColNames[1] == tableBCol2);
    REQUIRE(tableB->getNumberOfRows() == (tableBItems1.size() * tableBItems2.size()));

    // Check values stored at the correct position
    // Check if column values are correct
    auto col1Values = tableB->getColumnValues(tableBCol1);
    for (auto i : col1Values) {
        REQUIRE(tableBItems1.count(i));
    }
    // Check if row values are correct
    auto row1Values = tableB->getRow(0);
    std::vector<std::string> expectedValues {"a", "c"};
    REQUIRE(row1Values == expectedValues);

    // Check column values
    std::unordered_set<std::string> expectedRes = {"a", "b"};
    REQUIRE(tableB->getColumnValues(tableBCol1) == expectedRes);

    // Check column naming
    REQUIRE(tableB->getColumnNumber(tableBCol1) == 0);
    REQUIRE(tableB->getColumnNumber(tableBCol2) == 1);

    // Test matching column function
    std::vector<std::string> res = {tableBCol1};
    REQUIRE(tableB->hasMatchingColumns({tableBCol1, "TEST"}) == res);
    res = {};
    REQUIRE(tableB->hasMatchingColumns({"TEST"}) == res);

    // Test Insert row
    auto tableBCopy = ResultTable::createTableFromMap(tableBItems, tableBCol1, tableBCol2);
    std::vector<std::string> rowToInsert = {"g", "h"};
    tableBCopy->insertRow(rowToInsert);
    REQUIRE(tableBCopy->getNumberOfRows() == (tableBItems1.size() * tableBItems2.size() + 1));
    REQUIRE(tableBCopy->getRow(tableBCopy->getNumberOfRows() - 1) == rowToInsert);
}

TEST_CASE("Join One Matching Columns") {
    // Join table A and B
    auto res = ResultTable::joinTable(tableA, tableB);
    // Check result table column names
    std::vector<std::string> colNames = {tableBCol1, tableBCol2};
    REQUIRE(res->getColumnsNames() == colNames);
    // Check Number of row
    REQUIRE(res->getNumberOfRows() == 4);
    std::vector<std::string> row1 = {"a", "c"};
    std::vector<std::string> row2 = {"a", "d"};
    std::vector<std::string> row3 = {"b", "c"};
    std::vector<std::string> row4 = {"b", "d"};
    REQUIRE(res->getRow(0) == row1);
    REQUIRE(res->getRow(1) == row2);
    REQUIRE(res->getRow(2) == row3);
    REQUIRE(res->getRow(3) == row4);
}

TEST_CASE("Join two matching column") {
    // Join table B and C
    auto res = ResultTable::joinTable(tableB, tableC);
    // Check result table column names
    std::vector<std::string> colNames = {tableBCol1, tableBCol2};
    REQUIRE(res->getColumnsNames() == colNames);
    // Check Number of row
    REQUIRE(res->getNumberOfRows() == 2);
    std::vector<std::string> row1 = {"b", "c"};
    std::vector<std::string> row2 = {"b", "d"};
    REQUIRE(res->getRow(0) == row1);
    REQUIRE(res->getRow(1) == row2);

    res = ResultTable::joinTable(tableB, tableD);
    REQUIRE(res->getRow(0) == row1);
    REQUIRE(res->getRow(1) == row2);
}

TEST_CASE("Joining With Empty Table") {
    auto emptyTable = std::make_shared<ResultTable>(tableBCol1);
    // Join tableC and empty table
    auto res = ResultTable::joinTable(tableC, emptyTable);
    // Check result table column names
    std::vector<std::string> colNames = {tableBCol1, tableBCol2};
    REQUIRE(res->getColumnsNames() == colNames);
    // Check Number of row
    REQUIRE(res->getNumberOfRows() == 0);
}

TEST_CASE("Get Interested Values") {
    // Get One Column
    auto values = tableB->getInterestedValues({tableBCol1});
    REQUIRE(vectorToSet(values) == tableBItems1);

    // Get Two different Column
    values = tableB->getInterestedValues({tableBCol1, tableBCol2});
    std::unordered_set<std::string> expectedValues {"a c", "a d", "b c", "b d"};
    REQUIRE(vectorToSet(values) == expectedValues);

    // Get Similar Column
    values = tableB->getInterestedValues({tableBCol2, tableBCol2});
    expectedValues = {"c c", "d d"};
    // Duplicates are ignored
    REQUIRE(values.size() == 2);
    REQUIRE(vectorToSet(values) == expectedValues);
}

TEST_CASE("Insert Column") {
    // test table with 1 col and 4 rows
    auto testTable = ResultTable::createSingleColumnTable("col1", {"a", "b", "c", "d"});
    auto tableValues = testTable->getColumnOrderedValues({"col1"});
    std::vector<std::string> colToInsert {"1", "2", "3", "4"};
    std::string colName = "col2";
    testTable->insertCol(colName, colToInsert);
    REQUIRE(testTable->getColumnsNames().size() == 2);

    std::vector<std::string> expectedValue {tableValues.at(0), "1"};
    REQUIRE(testTable->getRow(0) == expectedValue);
    expectedValue = {tableValues.at(3), "4"};
    REQUIRE(testTable->getRow(3) == expectedValue);

    expectedValue = {"1", "2", "3", "4"};
    REQUIRE(testTable->getColumnOrderedValues(colName) == expectedValue);
    REQUIRE(testTable->getColumnOrderedValues("col1") == tableValues);

    // Different dimensions
    REQUIRE_THROWS(testTable->insertCol("col3", {"q", "w"}));
}
