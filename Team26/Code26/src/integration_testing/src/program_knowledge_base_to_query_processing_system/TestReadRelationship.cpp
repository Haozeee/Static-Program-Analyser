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

    auto assignManager = writeStorage->getAssignManager();
    assignManager->insertEntity(2);
    assignManager->insertEntity(4);
    assignManager->insertEntity(6);
    assignManager->insertEntity(7);
    assignManager->insertEntity(11);
    assignManager->insertEntity(13);
    assignManager->insertEntity(14);

    auto constantManager = writeStorage->getConstantManager();
    constantManager->insertEntity(0);
    constantManager->insertEntity(1);
    constantManager->insertEntity(2);

    auto ifManager = writeStorage->getIfManager();
    ifManager->insertEntity(3);
    ifManager->insertEntity(9);

    auto printManager = writeStorage->getPrintManager();
    printManager->insertEntity(5);
    printManager->insertEntity(10);
    printManager->insertEntity(12);
    
    auto procedureManager = writeStorage->getProcedureManager();
    procedureManager->insertEntity("test1");
    
    auto readManager = writeStorage->getReadManager();
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
    
    auto modifiesPManager = writeStorage->getModifiesPManager();
    modifiesPManager->insertRelationship("test1", "a");
    modifiesPManager->insertRelationship("test1", "x");
    modifiesPManager->insertRelationship("test1", "y");
    
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
    
    auto parentManager = writeStorage->getParentManager();
    parentManager->insertRelationship(3, 4);
    parentManager->insertRelationship(3, 5);
    parentManager->insertRelationship(3, 6);
    parentManager->insertRelationship(8, 9);
    parentManager->insertRelationship(8, 13);
    parentManager->insertRelationship(9, 10);
    parentManager->insertRelationship(9, 11);
    parentManager->insertRelationship(9, 12);
    
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
    
    auto usesPManager = writeStorage->getUsesPManager();
    usesPManager->insertRelationship("test1", "a");
    usesPManager->insertRelationship("test1", "x");
    usesPManager->insertRelationship("test1", "y");
    
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

    // test Follows
    std::list<std::string> q1a_results;
    std::string q1a = "stmt s; Select s such that Follows(1, s)"; 
    queryManager.process(q1a, q1a_results, storageManager->getReadStorage());

    std::list<std::string> a1a_results = {"2"};
    REQUIRE(q1a_results == a1a_results);

    std::list<std::string> q1b_results;
    std::string q1b = "stmt s; Select s such that Follows(1, 2)"; 
    queryManager.process(q1b, q1b_results, storageManager->getReadStorage());

    std::list<std::string> a1b_results = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"};
    q1b_results.sort(compare_int_string);
    REQUIRE(q1b_results == a1b_results);

    std::list<std::string> q1c_results;
    std::string q1c = "stmt s; Select s such that Follows(2, 1)";
    queryManager.process(q1c, q1c_results, storageManager->getReadStorage());

    std::list<std::string> a1c_results = {};
    REQUIRE(q1c_results == a1c_results);
    
    // test FollowsT
    std::list<std::string> q2a_results;
    std::string q2a = "stmt s; Select s such that Follows*(1, s)";
    queryManager.process(q2a, q2a_results, storageManager->getReadStorage());

    std::list<std::string> a2a_results = {"2", "3", "7", "8", "14"};
    q2a_results.sort(compare_int_string);
    REQUIRE(q2a_results == a2a_results);

    std::list<std::string> q2b_results;
    std::string q2b = "stmt s; Select s such that Follows*(s, 8)";
    queryManager.process(q2b, q2b_results, storageManager->getReadStorage());

    std::list<std::string> a2b_results = {"1", "2", "3", "7"};
    q2b_results.sort(compare_int_string);
    REQUIRE(q2b_results == a2b_results);

    // test Modifies
    std::list<std::string> q3a_results;
    std::string q3a = "stmt s; Select s such that Modifies(s, \"x\")";
    queryManager.process(q3a, q3a_results, storageManager->getReadStorage());

    std::list<std::string> a3a_results = {"2", "3", "4", "6", "8", "9", "11"};
    q3a_results.sort(compare_int_string);
    REQUIRE(q3a_results == a3a_results);

    std::list<std::string> q3b_results;
    std::string q3b = "variable v; Select v such that Modifies(8, v)";
    queryManager.process(q3b, q3b_results, storageManager->getReadStorage());

    std::list<std::string> a3b_results = {"x", "y"};
    REQUIRE(q3b_results == a3b_results);

    std::list<std::string> q3c_results;
    std::string q3c = "assign a; variable v; Select a such that Modifies(a, v)";
    queryManager.process(q3c, q3c_results, storageManager->getReadStorage());

    std::list<std::string> a3c_results = {"2", "4", "6", "7", "11", "13", "14"};
    q3c_results.sort(compare_int_string);
    REQUIRE(q3c_results == a3c_results);

    // test Parent
    std::list<std::string> q4a_results;
    std::string q4a = "stmt s; Select s such that Parent(8, s)";
    queryManager.process(q4a, q4a_results, storageManager->getReadStorage());

    std::list<std::string> a4a_results = {"9", "13"};
    q4a_results.sort(compare_int_string);
    REQUIRE(q4a_results == a4a_results);

    std::list<std::string> q4b_results;
    std::string q4b = "stmt s; Select s such that Parent(s, 3)";
    queryManager.process(q4b, q4b_results, storageManager->getReadStorage());

    std::list<std::string> a4b_results = {};
    REQUIRE(q4b_results == a4b_results);

    // test ParentT
    std::list<std::string> q5a_results;
    std::string q5a = "stmt s; Select s such that Parent*(8, s)";
    queryManager.process(q5a, q5a_results, storageManager->getReadStorage());

    std::list<std::string> a5a_results = {"9", "10", "11", "12", "13"};
    q5a_results.sort(compare_int_string);
    REQUIRE(q5a_results == a5a_results);

    std::list<std::string> q5b_results;
    std::string q5b = "stmt s; Select s such that Parent*(3, s)";
    queryManager.process(q5b, q5b_results, storageManager->getReadStorage());

    std::list<std::string> a5b_results = {"4", "5", "6"};
    q5b_results.sort(compare_int_string);
    REQUIRE(q5b_results == a5b_results);

    // test Uses
    std::list<std::string> q6a_results;
    std::string q6a = "stmt s; Select s such that Uses(s, \"a\")";
    queryManager.process(q6a, q6a_results, storageManager->getReadStorage());

    std::list<std::string> a6a_results = {"3"};
    REQUIRE(q6a_results == a6a_results);

    std::list<std::string> q6b_results;
    std::string q6b = "assign a; Select a such that Uses(a, \"x\")";
    queryManager.process(q6b, q6b_results, storageManager->getReadStorage());

    std::list<std::string> a6b_results = {"4", "14"};
    q6b_results.sort(compare_int_string);
    REQUIRE(q6b_results == a6b_results);

    std::list<std::string> q6c_results;
    std::string q6c = "print pn; variable v; Select v such that Uses(pn, v)";
    queryManager.process(q6c, q6c_results, storageManager->getReadStorage());

    std::list<std::string> a6c_results = {"x"};
    REQUIRE(q6c_results == a6c_results);
    


}