#include "catch.hpp"
#include "query_processing_system/evaluator/ResultTable.h"

// Create single tables to used for testing
std::unordered_set<std::string> tableAItems {"a", "b", "c"};
std::string tableACol = "col1";
auto tableA = ResultTable::createSingleColumnTable(tableACol, tableAItems);

// Create double columns to be used for testing
std::unordered_set<std::string> tableBItems1 {"a", "b", "c", "d"};
std::unordered_set<std::string> tableBItems2 {"a", "b", "c", "e"};
std::string tableBCol1 = "col1";
std::string tableBCol2 = "col2";
auto tableB = ResultTable::createDoubleColumnTable(tableBCol1, tableBItems1, tableBCol2, tableBItems2);

TEST_CASE("Single Table") {
    // Check correct dimensions of table
    REQUIRE(tableA->getNumberOfRows() == 1);
    // REQUIRE(tableA->getColumnsNames() == {tableACol});
    std::unordered_set<std::string> items {"a", "b", "c"};
    std::string colName = "col1";
    auto singleColTable = ResultTable::createSingleColumnTable(colName, items);
}

