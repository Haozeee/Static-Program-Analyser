#include "catch.hpp"
#include <memory>
#include <vector>
#include "query_processing_system/evaluator/QueryDb.h"
#include "query_processing_system/parser/DesignEntity.h"
#include "query_processing_system/parser/SelectClause.h"
#include "query_processing_system/parser/Synonym.h"

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

// Double column table with no rows
std::unordered_map<std::string, std::unordered_set<std::string>> table4Items {{"1", {"2", "3"}}};
auto table4 = ResultTable::createTableFromMap(table4Items, "col1", "col2");


TEST_CASE("Evaluate Boolean") {
    auto queryDB = QueryDb(nullptr);

    std::vector<std::string> expectedTrue {"TRUE"};
    std::vector<std::string> expectedFalse {"FALSE"};

    queryDB.addResult(table1);
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    queryDB = QueryDb(nullptr);
    queryDB.addResult(table2);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);

    queryDB = QueryDb(nullptr);
    queryDB.addResult(table3);
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    queryDB = QueryDb(nullptr);
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    // Table with no results
    auto table4 = std::make_shared<ResultTable>();
    table4->setNoResults();
    queryDB = QueryDb(nullptr);
    queryDB.addResult(table4);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);

    // Multiple tables
    queryDB = QueryDb(nullptr);
    queryDB.addResult(table4);
    queryDB.addResult(table1);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);

    queryDB = QueryDb(nullptr);
    queryDB.addResult(table1);
    queryDB.addResult(table3);
    REQUIRE(queryDB.getInterestedResults() == expectedTrue);

    queryDB = QueryDb(nullptr);
    queryDB.addResult(table1);
    queryDB.addResult(table2);
    REQUIRE(queryDB.getInterestedResults() == expectedFalse);
}

TEST_CASE("Missing Select Columns") {
    auto queryDB = QueryDb(nullptr);

    // Add select declarations
    std::vector<std::pair<SelectClauseItem, DesignEntity>> selectedCols;
    selectedCols.emplace_back(std::make_shared<Synonym>("col1"), DesignEntity::NONE);
    selectedCols.emplace_back(std::make_shared<Synonym>("col2"), DesignEntity::NONE);
    selectedCols.emplace_back(std::make_shared<Synonym>("col3"), DesignEntity::NONE);
    queryDB.setSelectedColumns(selectedCols);

    // Add table
    queryDB.addResult(table4);
    std::unordered_set<std::string> expectedCols = {"col1", "col2"};
    REQUIRE(queryDB.getAllColumnsInResults() == expectedCols);
}
