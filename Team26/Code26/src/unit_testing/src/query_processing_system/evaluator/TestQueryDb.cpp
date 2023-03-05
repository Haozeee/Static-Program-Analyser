#include "catch.hpp"
#include <memory>
#include "query_processing_system/evaluator/QueryDb.h"

// Single column table
std::unordered_set<std::string> table1Items {"a", "b", "c"};
std::string table1Col = "col1";
auto table1 = ResultTable::createSingleColumnTable(table1Col, table1Items);

// Single column table with no rows
std::unordered_set<std::string> table2Items {};
std::string table2Col = "col1";
auto table2 = ResultTable::createSingleColumnTable(table2Col, table2Items);

// Table with no column
auto table3 = std::make_shared<ResultTable>();

TEST_CASE("Evaluate Boolean") {
    auto queryDB = QueryDb();

    std::vector<std::string> expectedTrue {"TRUE"};
    std::vector<std::string> expectedFalse {"FALSE"};

    queryDB.addResult(table1);
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    queryDB = QueryDb();
    queryDB.addResult(table2);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);

    queryDB = QueryDb();
    queryDB.addResult(table3);
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    queryDB = QueryDb();
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    // Table with no results
    auto table4 = std::make_shared<ResultTable>();
    table4->setNoResults();
    queryDB = QueryDb();
    queryDB.addResult(table4);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);

    // Multiple tables
    queryDB = QueryDb();
    queryDB.addResult(table4);
    queryDB.addResult(table1);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);

    queryDB = QueryDb();
    queryDB.addResult(table1);
    queryDB.addResult(table3);
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    queryDB = QueryDb();
    queryDB.addResult(table1);
    queryDB.addResult(table2);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);
}
