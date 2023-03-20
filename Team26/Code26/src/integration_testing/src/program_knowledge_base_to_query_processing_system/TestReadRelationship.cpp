#include "catch.hpp"
#include <string>
#include <utility>
#include "program_knowledge_base/StorageManager.h"
#include "query_processing_system/QueryManager.h"
#include "../test_helpers/compare_int_string.h"

// refer to ../test_helpers/source_relationship_test.txt for source program of following test
TEST_CASE("Test reading relationships for all managers") {
    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    QueryManager queryManager;
    auto writeStorage = storageManager->getWriteStorage();

    // populate PKB
    auto assignManager = writeStorage->getAssignManager();
    assignManager->insertEntity(2);
    assignManager->insertEntity(4);
    assignManager->insertEntity(6);
    assignManager->insertEntity(7);
    assignManager->insertEntity(11);
    assignManager->insertEntity(13);
    assignManager->insertEntity(14);

    auto callProcedureManager = writeStorage->getCallProcedureManager();
    callProcedureManager->insertEntity("test2");
    callProcedureManager->insertEntity("test3");

    auto callStmtNoManager = writeStorage->getCallStmtNoManager();
    callStmtNoManager->insertEntity(15);
    callStmtNoManager->insertEntity(17);

    auto constantManager = writeStorage->getConstantManager();
    constantManager->insertEntity(0);
    constantManager->insertEntity(1);
    constantManager->insertEntity(2);

    auto ifManager = writeStorage->getIfManager();
    ifManager->insertEntity(3);
    ifManager->insertEntity(9);

    auto printVariableManager = writeStorage->getPrintVariableManager();
    printVariableManager->insertEntity("x");

    auto printStmtNoManager = writeStorage->getPrintStmtNoManager();
    printStmtNoManager->insertEntity(5);
    printStmtNoManager->insertEntity(10);
    printStmtNoManager->insertEntity(12);
    
    auto procedureManager = writeStorage->getProcedureManager();
    procedureManager->insertEntity("test1");
    
    auto readManager = writeStorage->getReadStmtNoManager();
    readManager->insertEntity(1);
    
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
    stmtManager->insertEntity(12);
    stmtManager->insertEntity(13);
    stmtManager->insertEntity(14);

    auto variableManager = writeStorage->getVariableManager();
    variableManager->insertEntity("a");
    variableManager->insertEntity("x");
    variableManager->insertEntity("y");

    auto whileManager = writeStorage->getWhileManager();
    whileManager->insertEntity(8);
    
    auto followsManager = writeStorage->getFollowsManager();
    followsManager->insertRelationship(1, 2);
    followsManager->insertRelationship(2, 3);
    followsManager->insertRelationship(4, 5);
    followsManager->insertRelationship(3, 7);
    followsManager->insertRelationship(7, 8);
    followsManager->insertRelationship(8, 14);
    followsManager->insertRelationship(9, 13);
    followsManager->insertRelationship(11, 12);
    followsManager->insertRelationship(14, 15);
    followsManager->insertRelationship(16, 17);
    followsManager->setReverse();

    auto followsTManager = writeStorage->getFollowsTManager();
    followsTManager->insertRelationship(1, 2);
    followsTManager->insertRelationship(1, 3);
    followsTManager->insertRelationship(1, 7);
    followsTManager->insertRelationship(1, 8);
    followsTManager->insertRelationship(1, 14);
    followsTManager->insertRelationship(2, 3);
    followsTManager->insertRelationship(2, 7);
    followsTManager->insertRelationship(2, 8);
    followsTManager->insertRelationship(2, 14);
    followsTManager->insertRelationship(4, 5);
    followsTManager->insertRelationship(3, 7);
    followsTManager->insertRelationship(3, 8);
    followsTManager->insertRelationship(3, 14);
    followsTManager->insertRelationship(7, 8);
    followsTManager->insertRelationship(7, 14);
    followsTManager->insertRelationship(8, 14);
    followsTManager->insertRelationship(9, 13);
    followsTManager->insertRelationship(11, 12);
    followsTManager->insertRelationship(1, 15);
    followsTManager->insertRelationship(2, 15);
    followsTManager->insertRelationship(3, 15);
    followsTManager->insertRelationship(7, 15);
    followsTManager->insertRelationship(8, 15);
    followsTManager->insertRelationship(14, 15);
    followsTManager->insertRelationship(16, 17);
    followsTManager->setReverse();
    
    auto modifiesPManager = writeStorage->getModifiesPManager();
    modifiesPManager->insertRelationship("test1", "a");
    modifiesPManager->insertRelationship("test1", "b");
    modifiesPManager->insertRelationship("test1", "c");
    modifiesPManager->insertRelationship("test1", "x");
    modifiesPManager->insertRelationship("test1", "y");
    modifiesPManager->insertRelationship("test2", "b");
    modifiesPManager->insertRelationship("test2", "c");
    modifiesPManager->insertRelationship("test3", "c");
    modifiesPManager->setReverse();
    
    auto modifiesSManager = writeStorage->getModifiesSManager();
    modifiesSManager->insertRelationship(1,"a");
    modifiesSManager->insertRelationship(2,"x");
    modifiesSManager->insertRelationship(3,"x");
    modifiesSManager->insertRelationship(4,"x");
    modifiesSManager->insertRelationship(6,"x");
    modifiesSManager->insertRelationship(7,"y");
    modifiesSManager->insertRelationship(8,"x");
    modifiesSManager->insertRelationship(8,"y");
    modifiesSManager->insertRelationship(9,"x");
    modifiesSManager->insertRelationship(11,"x");
    modifiesSManager->insertRelationship(13,"y");
    modifiesSManager->insertRelationship(14,"y");
    modifiesSManager->insertRelationship(15, "b");
    modifiesSManager->insertRelationship(15, "c");
    modifiesSManager->insertRelationship(16, "b");
    modifiesSManager->insertRelationship(17, "c");
    modifiesSManager->insertRelationship(18, "c");
    modifiesSManager->setReverse();
    
    auto parentManager = writeStorage->getParentManager();
    parentManager->insertRelationship(3, 4);
    parentManager->insertRelationship(3, 5);
    parentManager->insertRelationship(3, 6);
    parentManager->insertRelationship(8, 9);
    parentManager->insertRelationship(8, 13);
    parentManager->insertRelationship(9, 10);
    parentManager->insertRelationship(9, 11);
    parentManager->insertRelationship(9, 12);
    parentManager->setReverse();
    
    auto parentTManager = writeStorage->getParentTManager();
    parentTManager->insertRelationship(3, 4);
    parentTManager->insertRelationship(3, 5);
    parentTManager->insertRelationship(3, 6);
    parentTManager->insertRelationship(8, 9);
    parentTManager->insertRelationship(8, 10);
    parentTManager->insertRelationship(8, 11);
    parentTManager->insertRelationship(8, 12);
    parentTManager->insertRelationship(8, 13);
    parentTManager->insertRelationship(9, 10);
    parentTManager->insertRelationship(9, 11);
    parentTManager->insertRelationship(9, 12);
    parentTManager->setReverse();
    
    auto usesPManager = writeStorage->getUsesPManager();
    usesPManager->insertRelationship("test1", "a");
    usesPManager->insertRelationship("test1", "x");
    usesPManager->insertRelationship("test1", "y");
    usesPManager->setReverse();
    
    auto usesSManager = writeStorage->getUsesSManager();
    usesSManager->insertRelationship(3, "a");
    usesSManager->insertRelationship(3, "x");
    usesSManager->insertRelationship(4, "x");
    usesSManager->insertRelationship(5, "x");
    usesSManager->insertRelationship(8, "x");
    usesSManager->insertRelationship(8, "y");
    usesSManager->insertRelationship(9, "x");
    usesSManager->insertRelationship(10, "x");
    usesSManager->insertRelationship(12, "x");
    usesSManager->insertRelationship(13, "y");
    usesSManager->insertRelationship(14, "x");
    usesSManager->setReverse();

    auto callsPManager = writeStorage->getCallsPManager();
    callsPManager->insertRelationship("test1", "test2");
    callsPManager->insertRelationship("test2", "test3");

    auto callsSManager = writeStorage->getCallsSManager();
    callsSManager->insertRelationship(15, "test2");
    callsSManager->insertRelationship(17, "test3");

    auto callsTManager = writeStorage->getCallsTManager();
    callsTManager->insertRelationship("test1", "test2");
    callsTManager->insertRelationship("test1", "test3");
    callsTManager->insertRelationship("test2", "test3");
    
    auto ifCondManager = writeStorage->getIfCondManager();
    ifCondManager->insertRelationship(3, "a");
    ifCondManager->insertRelationship(9, "x");
    
    auto nextManager = writeStorage->getNextManager();
    nextManager->insertRelationship(1, 2);
    nextManager->insertRelationship(2, 3);
    nextManager->insertRelationship(3, 4);
    nextManager->insertRelationship(3, 6);
    nextManager->insertRelationship(4, 5);
    nextManager->insertRelationship(5, 7);
    nextManager->insertRelationship(6, 7);
    nextManager->insertRelationship(7, 8);
    nextManager->insertRelationship(8, 9);
    nextManager->insertRelationship(8, 14);
    nextManager->insertRelationship(9, 10);
    nextManager->insertRelationship(9, 11);
    nextManager->insertRelationship(10, 13);
    nextManager->insertRelationship(11, 12);
    nextManager->insertRelationship(12, 13);
    nextManager->insertRelationship(13, 8);
    nextManager->insertRelationship(14, 15);
    nextManager->insertRelationship(16, 17);

    auto whileCondManager = writeStorage->getWhileCondManager();
    whileCondManager->insertRelationship(8, "y");

    // test Follows
    std::list<std::string> q1aResults;
    std::string q1a = "stmt s; Select s such that Follows(1, s)"; 
    queryManager.process(q1a, q1aResults, storageManager->getReadStorage());

    std::list<std::string> a1aResults = {"2"};
    REQUIRE(q1aResults == a1aResults);

    std::list<std::string> q1bResults;
    std::string q1b = "stmt s; Select s such that Follows(1, 2)"; 
    queryManager.process(q1b, q1bResults, storageManager->getReadStorage());

    std::list<std::string> a1bResults = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"};
    q1bResults.sort(compare_int_string);
    REQUIRE(q1bResults == a1bResults);

    std::list<std::string> q1cResults;
    std::string q1c = "stmt s; Select s such that Follows(2, 1)";
    queryManager.process(q1c, q1cResults, storageManager->getReadStorage());

    std::list<std::string> a1cResults = {};
    REQUIRE(q1cResults == a1cResults);
    
    // test FollowsT
    std::list<std::string> q2aResults;
    std::string q2a = "stmt s; Select s such that Follows*(1, s)";
    queryManager.process(q2a, q2aResults, storageManager->getReadStorage());

    std::list<std::string> a2aResults = {"2", "3", "7", "8", "14"};
    q2aResults.sort(compare_int_string);
    REQUIRE(q2aResults == a2aResults);

    std::list<std::string> q2bResults;
    std::string q2b = "stmt s; Select s such that Follows*(s, 8)";
    queryManager.process(q2b, q2bResults, storageManager->getReadStorage());

    std::list<std::string> a2bResults = {"1", "2", "3", "7"};
    q2bResults.sort(compare_int_string);
    REQUIRE(q2bResults == a2bResults);

    // test Modifies
    std::list<std::string> q3aResults;
    std::string q3a = "stmt s; Select s such that Modifies(s, \"x\")";
    queryManager.process(q3a, q3aResults, storageManager->getReadStorage());

    std::list<std::string> a3aResults = {"2", "3", "4", "6", "8", "9", "11"};
    q3aResults.sort(compare_int_string);
    REQUIRE(q3aResults == a3aResults);

    std::list<std::string> q3bResults;
    std::string q3b = "variable v; Select v such that Modifies(8, v)";
    queryManager.process(q3b, q3bResults, storageManager->getReadStorage());

    std::list<std::string> a3bResults = {"x", "y"};
    q3bResults.sort();
    REQUIRE(q3bResults == a3bResults);

    std::list<std::string> q3cResults;
    std::string q3c = "assign a; variable v; Select a such that Modifies(a, v)";
    queryManager.process(q3c, q3cResults, storageManager->getReadStorage());

    std::list<std::string> a3cResults = {"2", "4", "6", "7", "11", "13", "14"};
    q3cResults.sort(compare_int_string);
    REQUIRE(q3cResults == a3cResults);

    // test Parent
    std::list<std::string> q4aResults;
    std::string q4a = "stmt s; Select s such that Parent(8, s)";
    queryManager.process(q4a, q4aResults, storageManager->getReadStorage());

    std::list<std::string> a4aResults = {"9", "13"};
    q4aResults.sort(compare_int_string);
    REQUIRE(q4aResults == a4aResults);

    std::list<std::string> q4bResults;
    std::string q4b = "stmt s; Select s such that Parent(s, 3)";
    queryManager.process(q4b, q4bResults, storageManager->getReadStorage());

    std::list<std::string> a4bResults = {};
    REQUIRE(q4bResults == a4bResults);

    // test ParentT
    std::list<std::string> q5aResults;
    std::string q5a = "stmt s; Select s such that Parent*(8, s)";
    queryManager.process(q5a, q5aResults, storageManager->getReadStorage());

    std::list<std::string> a5aResults = {"9", "10", "11", "12", "13"};
    q5aResults.sort(compare_int_string);
    REQUIRE(q5aResults == a5aResults);

    std::list<std::string> q5bResults;
    std::string q5b = "stmt s; Select s such that Parent*(3, s)";
    queryManager.process(q5b, q5bResults, storageManager->getReadStorage());

    std::list<std::string> a5bResults = {"4", "5", "6"};
    q5bResults.sort(compare_int_string);
    REQUIRE(q5bResults == a5bResults);

    // test Uses
    std::list<std::string> q6aResults;
    std::string q6a = "stmt s; Select s such that Uses(s, \"a\")";
    queryManager.process(q6a, q6aResults, storageManager->getReadStorage());

    std::list<std::string> a6aResults = {"3"};
    REQUIRE(q6aResults == a6aResults);

    std::list<std::string> q6bResults;
    std::string q6b = "assign a; Select a such that Uses(a, \"x\")";
    queryManager.process(q6b, q6bResults, storageManager->getReadStorage());

    std::list<std::string> a6bResults = {"4", "14"};
    q6bResults.sort(compare_int_string);
    REQUIRE(q6bResults == a6bResults);

    std::list<std::string> q6cResults;
    std::string q6c = "print pn; variable v; Select v such that Uses(pn, v)";
    queryManager.process(q6c, q6cResults, storageManager->getReadStorage());

    std::list<std::string> a6cResults = {"x"};
    REQUIRE(q6cResults == a6cResults);

    // test Calls
    std::list<std::string> q7aResults;
    std::string q7a = "call cl; Select cl";
    queryManager.process(q7a, q7aResults, storageManager->getReadStorage());

    std::list<std::string> a7aResults = {"15", "17"};
    q7aResults.sort(compare_int_string);
    REQUIRE(q7aResults == a7aResults);

    // test next
    std::list<std::string> q8aResults;
    std::string q8a = "stmt s; read r; Select s such that Next(s, r)";
    queryManager.process(q8a, q8aResults, storageManager->getReadStorage());

    std::list<std::string> a8aResults = {};
    REQUIRE(q8aResults == a8aResults);

    std::list<std::string> q8bResults;
    std::string q8b = "stmt s; Select s such that Next(9, s)";
    queryManager.process(q8b, q8bResults, storageManager->getReadStorage());

    std::list<std::string> a8bResults = {"10", "11"};
    q8bResults.sort(compare_int_string);
    REQUIRE(q8bResults == a8bResults);
}
