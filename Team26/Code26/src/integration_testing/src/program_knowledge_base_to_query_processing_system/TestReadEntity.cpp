#include "catch.hpp"
#include <string>
#include <utility>
#include "program_knowledge_base/StorageManager.h"
#include "query_processing_system/QueryManager.h"
#include "../test_helpers/compare_int_string.h"

// refer to ../test_helpers/source_entity_test.txt for source program of following test
TEST_CASE("Test reading entity for all manager") {
    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    QueryManager queryManager;
    auto writeStorage = storageManager->getWriteStorage();

    // populate PKB
    auto assignManager = writeStorage->getAssignManager();
    assignManager->insertEntity(1);
    assignManager->insertEntity(4);
    assignManager->insertEntity(5);
    assignManager->insertEntity(6);
    assignManager->insertEntity(9);

    auto callProcedureManager = writeStorage->getCallProcedureManager();
    callProcedureManager->insertEntity("test2");

    auto callStmtNoManager = writeStorage->getCallStmtNoManager();
    callStmtNoManager->insertEntity(2);

    auto constantManager = writeStorage->getConstantManager();
    constantManager->insertEntity(0);
    constantManager->insertEntity(1);
    constantManager->insertEntity(3);
    constantManager->insertEntity(10);

    auto ifManager = writeStorage->getIfManager();
    ifManager->insertEntity(3);

    auto printStmtNoManager = writeStorage->getPrintStmtNoManager();
    printStmtNoManager->insertEntity(8);

    auto printVariableManager = writeStorage->getPrintVariableManager();
    printVariableManager->insertEntity("x");

    auto procedureManager = writeStorage->getProcedureManager();
    procedureManager->insertEntity("test1");
    procedureManager->insertEntity("test2");

    auto readManager = writeStorage->getReadStmtNoManager();
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
    std::list<std::string> q1Results;
    std::string q1 = "assign a; Select a";
    queryManager.process(q1, q1Results, storageManager->getReadStorage());

    std::list<std::string> a1Results = {"1", "4", "5", "6", "9"};
    q1Results.sort(compare_int_string);
    REQUIRE(q1Results == a1Results);

    // test Call
    std::list<std::string> q2Results;
    std::string q2 = "call cl; Select cl";
    queryManager.process(q2, q2Results, storageManager->getReadStorage());

    std::list<std::string> a2Results = {"2"};
    REQUIRE(q2Results == a2Results);

    // test Constant
    std::list<std::string> q3Results;
    std::string q3 = "constant c; Select c";
    queryManager.process(q3, q3Results, storageManager->getReadStorage());

    std::list<std::string> a3Results = {"0", "1", "3", "10"};
    q3Results.sort(compare_int_string);
    REQUIRE(q3Results == a3Results);

    // test If
    std::list<std::string> q4Results;
    std::string q4 = "if ifs; Select ifs";
    queryManager.process(q4, q4Results, storageManager->getReadStorage());

    std::list<std::string> a4Results = {"3"};
    REQUIRE(q4Results == a4Results);

    // test Print
    std::list<std::string> q5Results;
    std::string q5 = "print pn; Select pn";
    queryManager.process(q5, q5Results, storageManager->getReadStorage());

    std::list<std::string> a5Results = {"8"};
    REQUIRE(q5Results == a5Results);

    // test Procedure
    std::list<std::string> q6Results;
    std::string q6 = "procedure p; Select p";
    queryManager.process(q6, q6Results, storageManager->getReadStorage());

    std::list<std::string> a6Results = {"test2", "test1"};
    REQUIRE(q6Results == a6Results);

    // test Read
    std::list<std::string> q7Results;
    std::string q7 = "read r; Select r";
    queryManager.process(q7, q7Results, storageManager->getReadStorage());

    std::list<std::string> a7Results = {"10", "11"};
    q7Results.sort(compare_int_string);
    REQUIRE(q7Results == a7Results);

    // test Stmt
    std::list<std::string> q8Results;
    std::string q8 = "stmt s; Select s";
    queryManager.process(q8, q8Results, storageManager->getReadStorage());

    std::list<std::string> a8Results = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    q8Results.sort(compare_int_string);
    REQUIRE(q8Results == a8Results);

    // test Variable
    std::list<std::string> q9Results;
    std::string q9 = "variable v; Select v";
    queryManager.process(q9, q9Results, storageManager->getReadStorage());

    std::list<std::string> a9Results = {"a", "b", "x", "y"};
    q9Results.sort();
    REQUIRE(q9Results == a9Results);

    // test While
    std::list<std::string> q10Results;
    std::string q10 = "while w; Select w";
    queryManager.process(q10, q10Results, storageManager->getReadStorage());

    std::list<std::string> a10Results = {"7"};
    REQUIRE(q10Results == a10Results);
}
