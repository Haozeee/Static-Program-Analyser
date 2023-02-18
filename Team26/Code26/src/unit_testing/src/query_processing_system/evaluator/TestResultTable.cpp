#include "catch.hpp"
#include "query_processing_system/evaluator/ResultTable.h"

// Create single tables to used for testing
std::unordered_set<std::string> tableAItems {"a", "b", "c"};
std::string tableACol = "col1";
auto tableA = ResultTable::createSingleColumnTable(tableACol, tableAItems);

// Create double columns table to be used for testing
std::unordered_set<std::string> tableBItems1 {"a", "b"};
std::unordered_set<std::string> tableBItems2 {"c", "d"};
std::string tableBCol1 = "col1";
std::string tableBCol2 = "col2";
auto tableB = ResultTable::createDoubleColumnTable(tableBCol1, tableBItems1, tableBCol2, tableBItems2);

// Create double columns table to be used for testing
std::unordered_set<std::string> tableCItems1 {"b"};
std::unordered_set<std::string> tableCItems2 {"c", "d"};
auto tableC = ResultTable::createDoubleColumnTable(tableBCol1, tableCItems1, tableBCol2, tableCItems2);

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
    std::vector<std::string> rowToInsert = {"g", "h"};
    tableB->insertRow(rowToInsert);
    REQUIRE(tableB->getNumberOfRows() == (tableBItems1.size() * tableBItems2.size() + 1));
    REQUIRE(tableB->getRow(tableB->getNumberOfRows() - 1) == rowToInsert);
}

TEST_CASE("Join One Matching Columns") {
    // Join table A and B
    auto res = ResultTable::joinOnColumns(tableA, tableB, {tableBCol1});
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
    auto res = ResultTable::joinOnColumns(tableB, tableC, {tableBCol1, tableBCol2});
    // Check result table column names
    std::vector<std::string> colNames = {tableBCol1, tableBCol2};
    REQUIRE(res->getColumnsNames() == colNames);
    // Check Number of row
    REQUIRE(res->getNumberOfRows() == 2);
    std::vector<std::string> row1 = {"b", "c"};
    std::vector<std::string> row2 = {"b", "d"};
    REQUIRE(res->getRow(0) == row1);
    REQUIRE(res->getRow(1) == row2);
}

TEST_CASE("Joining With Empty Table") {
    auto emptyTable = std::make_shared<ResultTable>(tableBCol1);
    // Join tableC and empty table
    auto res = ResultTable::joinOnColumns(tableC, emptyTable, {tableBCol1});
    // Check result table column names
    std::vector<std::string> colNames = {tableBCol1, tableBCol2};
    REQUIRE(res->getColumnsNames() == colNames);
    // Check Number of row
    REQUIRE(res->getNumberOfRows() == 0);
}
