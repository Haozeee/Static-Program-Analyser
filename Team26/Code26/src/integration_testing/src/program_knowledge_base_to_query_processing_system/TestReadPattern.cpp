#include "catch.hpp"
#include <string>
#include <utility>

#include "common/parser/ShuntingYardParser.h"
#include "program_knowledge_base/StorageManager.h"
#include "query_processing_system/QueryManager.h"
#include "../test_helpers/compare_int_string.h"

// refer to ../test_helpers/source_pattern_test.txt for source program of following test
TEST_CASE("Test reading pattern") {
    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    QueryManager queryManager;
    auto writeStorage = storageManager->getWriteStorage();

    // populate PKB
    auto assignManager = writeStorage->getAssignManager();
    assignManager->insertEntity(1);
    assignManager->insertEntity(2);
    assignManager->insertEntity(4);
    assignManager->insertEntity(5);

    auto constantManager = writeStorage->getConstantManager();
    constantManager->insertEntity(3);
    constantManager->insertEntity(5);

    auto procedureManager = writeStorage->getProcedureManager();
    procedureManager->insertEntity("test1");

    auto readManager = writeStorage->getReadStmtNoManager();
    readManager->insertEntity(3);

    auto stmtManager = writeStorage->getStmtManager();
    stmtManager->insertEntity(1);
    stmtManager->insertEntity(2);
    stmtManager->insertEntity(3);
    stmtManager->insertEntity(4);
    stmtManager->insertEntity(5);

    auto variableManager = writeStorage->getVariableManager();
    variableManager->insertEntity("x");
    variableManager->insertEntity("y");
    variableManager->insertEntity("z");

    auto patternManager = writeStorage->getPatternManager();
    auto node1 = ShuntingYardParser::parse("5");
    auto node2 = ShuntingYardParser::parse("x*3");
    auto node3 = ShuntingYardParser::parse("x*y+x/y");
    auto node4 = ShuntingYardParser::parse("z");
    patternManager->insertPattern(1, "x", node1);
    patternManager->insertPattern(2, "y", node2);
    patternManager->insertPattern(4, "z", node3);
    patternManager->insertPattern(5, "x", node4);

    // test Pattern
    std::list<std::string> q1_results;
    std::string q1 = "assign a; Select a pattern a(_, _)";
    queryManager.process(q1, q1_results, storageManager->getReadStorage());

    std::list<std::string> a1_results = {"1", "2", "4", "5"};
    q1_results.sort(compare_int_string);
    REQUIRE(q1_results == a1_results);

    std::list<std::string> q2_results;
    std::string q2 = "assign a; Select a pattern a(\"x\", _)";
    queryManager.process(q2, q2_results, storageManager->getReadStorage());

    std::list<std::string> a2_results = {"1", "5"};
    q2_results.sort(compare_int_string);
    REQUIRE(q2_results == a2_results);

    std::list<std::string> q3_results;
    std::string q3 = "assign a; Select a pattern a(_, _\"x*y\"_)";
    queryManager.process(q3, q3_results, storageManager->getReadStorage());

    std::list<std::string> a3_results = {"4"};
    REQUIRE(q3_results == a3_results);

    std::list<std::string> q4_results;
    std::string q4 = "assign a; Select a pattern a(_, _\"x\"_)";
    queryManager.process(q4, q4_results, storageManager->getReadStorage());

    std::list<std::string> a4_results = {"2", "4"};
    q4_results.sort(compare_int_string);
    REQUIRE(q4_results == a4_results);

    std::list<std::string> q5_results;
    std::string q5 = "assign a; Select a pattern a(_, \"x\")";
    queryManager.process(q5, q5_results, storageManager->getReadStorage());

    std::list<std::string> a5_results = {};
    REQUIRE(q5_results == a5_results);
}
