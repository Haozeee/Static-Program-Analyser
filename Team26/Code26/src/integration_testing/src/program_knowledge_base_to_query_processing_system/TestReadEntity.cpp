#include "catch.hpp"
#include <string>
#include <utility>
#include "program_knowledge_base/StorageManager.h"
#include "query_processing_system/QueryManager.h"

// helper function to compare list of int strings
bool compare_int_string(const std::string& str1, const std::string& str2) {
    return std::stoi(str1) < std::stoi(str2);
}

TEST_CASE("Test reading entity for all manager") {
    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    QueryManager queryManager;
    auto writeStorage = storageManager->getWriteStorage();

    auto assignManager = writeStorage->getAssignManager();
    assignManager->insertEntity(1);
    assignManager->insertEntity(4);
    assignManager->insertEntity(5);
    assignManager->insertEntity(6);
    assignManager->insertEntity(9);

    auto callManager = writeStorage->getCallManager();
    callManager->insertEntity(2);

    auto constantManager = writeStorage->getConstantManager();
    constantManager->insertEntity(0);
    constantManager->insertEntity(1);
    constantManager->insertEntity(3);
    constantManager->insertEntity(10);

    auto ifManager = writeStorage->getIfManager();
    ifManager->insertEntity(3);

    auto printManager = writeStorage->getPrintManager();
    printManager->insertEntity(8);

    auto procedureManager = writeStorage->getProcedureManager();
    procedureManager->insertEntity("test1");
    procedureManager->insertEntity("test2");

    auto readManager = writeStorage->getReadManager();
    readManager->insertEntity(10);
    readManager->insertEntity(11);

    auto stmtManager = writeStorage->getStmtManager();
    stmtManager->insertEntity(1);
    stmtManager->insertEntity(2);
    stmtManager->insertEntity(3);
    stmtManager->insertEntity(4);
    stmtManager->insertEntity(5);
    stmtManager->insertEntity(6);
    stmtManager->insertEntity(7);
    stmtManager->insertEntity(8);
    stmtManager->insertEntity(9);
    stmtManager->insertEntity(10);
    stmtManager->insertEntity(11);

    auto variableManager = writeStorage->getVariableManager();
    variableManager->insertEntity("a");
    variableManager->insertEntity("b");
    variableManager->insertEntity("x");
    variableManager->insertEntity("y");

    auto whileManager = writeStorage->getWhileManager();
    whileManager->insertEntity(7);

    // test Assign
    std::list<std::string> q1_results;
    std::string q1 = "assign a; Select a"; // to be declared
    queryManager.process(q1, q1_results, storageManager->getReadStorage());

    std::list<std::string> a1_results = {"1", "4", "5", "6", "9"};
    q1_results.sort(compare_int_string);
    REQUIRE(q1_results == a1_results);

    // test Call
    std::list<std::string> q2_results;
    std::string q2 = "call cl; Select cl"; // to be declared
    queryManager.process(q2, q2_results, storageManager->getReadStorage());

    std::list<std::string> a2_results = {"2"};
    REQUIRE(q2_results == a2_results);

    // test Constant
    std::list<std::string> q3_results;
    std::string q3 = "constant c; Select c"; // to be declared
    queryManager.process(q3, q3_results, storageManager->getReadStorage());

    std::list<std::string> a3_results = {"0", "1", "3", "10"};
    q3_results.sort(compare_int_string);
    REQUIRE(q3_results == a3_results);

    // test If
    std::list<std::string> q4_results;
    std::string q4 = "if ifs; Select ifs"; // to be declared
    queryManager.process(q4, q4_results, storageManager->getReadStorage());

    std::list<std::string> a4_results = {"3"};
    REQUIRE(q4_results == a4_results);

    // test Print
    std::list<std::string> q5_results;
    std::string q5 = "print pn; Select pn"; // to be declared
    queryManager.process(q5, q5_results, storageManager->getReadStorage());

    std::list<std::string> a5_results = {"8"};
    REQUIRE(q5_results == a5_results);

    // test Procedure
    std::list<std::string> q6_results;
    std::string q6 = "procedure p; Select p"; // to be declared
    queryManager.process(q6, q6_results, storageManager->getReadStorage());

    std::list<std::string> a6_results = {"test1", "test2"};
    REQUIRE(q6_results == a6_results);

    // test Read
    std::list<std::string> q7_results;
    std::string q7 = "read r; Select r"; // to be declared
    queryManager.process(q7, q7_results, storageManager->getReadStorage());

    std::list<std::string> a7_results = {"10", "11"};
    q7_results.sort(compare_int_string);
    REQUIRE(q7_results == a7_results);

    // test Stmt
    std::list<std::string> q8_results;
    std::string q8 = "stmt s; Select s"; // to be declared
    queryManager.process(q8, q8_results, storageManager->getReadStorage());

    std::list<std::string> a8_results = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    q8_results.sort(compare_int_string);
    REQUIRE(q8_results == a8_results);

    // test Variable
    std::list<std::string> q9_results;
    std::string q9 = "variable v; Select v"; // to be declared
    queryManager.process(q9, q9_results, storageManager->getReadStorage());

    std::list<std::string> a9_results = {"a", "b", "x", "y"};
    q9_results.sort();
    REQUIRE(q9_results == a9_results);

    // test While
    std::list<std::string> q10_results;
    std::string q10 = "while w; Select w"; // to be declared
    queryManager.process(q10, q10_results, storageManager->getReadStorage());

    std::list<std::string> a10_results = {"7"};
    REQUIRE(q10_results == a10_results);
}
