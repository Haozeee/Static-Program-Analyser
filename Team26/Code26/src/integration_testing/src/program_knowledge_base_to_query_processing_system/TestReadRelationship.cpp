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
    procedureManager->insertEntity("test2");
    procedureManager->insertEntity("test3");

    auto readStmtManager = writeStorage->getReadStmtNoManager();
    readStmtManager->insertEntity(1);
    readStmtManager->insertEntity(16);
    readStmtManager->insertEntity(18);

    auto readVariableManager = writeStorage->getReadVariableManager();
    readVariableManager->insertEntity("a");
    readVariableManager->insertEntity("b");
    readVariableManager->insertEntity("c");

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
    stmtManager->insertEntity(15);
    stmtManager->insertEntity(16);
    stmtManager->insertEntity(17);
    stmtManager->insertEntity(18);

    auto variableManager = writeStorage->getVariableManager();
    variableManager->insertEntity("a");
    variableManager->insertEntity("b");
    variableManager->insertEntity("c");
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
    followsTManager->insertRelationship(1, 15);
    followsTManager->insertRelationship(2, 3);
    followsTManager->insertRelationship(2, 7);
    followsTManager->insertRelationship(2, 8);
    followsTManager->insertRelationship(2, 14);
    followsTManager->insertRelationship(2, 15);
    followsTManager->insertRelationship(4, 5);
    followsTManager->insertRelationship(3, 7);
    followsTManager->insertRelationship(3, 8);
    followsTManager->insertRelationship(3, 14);
    followsTManager->insertRelationship(3, 15);
    followsTManager->insertRelationship(7, 8);
    followsTManager->insertRelationship(7, 14);
    followsTManager->insertRelationship(7, 15);
    followsTManager->insertRelationship(8, 14);
    followsTManager->insertRelationship(8, 15);
    followsTManager->insertRelationship(9, 13);
    followsTManager->insertRelationship(11, 12);
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

    std::list<std::string> a1bResults = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13",
                                         "14", "15", "16", "17", "18"};
    q1bResults.sort(compare_int_string);
    REQUIRE(q1bResults == a1bResults);

    std::list<std::string> q1cResults;
    std::string q1c = "stmt s; Select s such that Follows(2, 1)";
    queryManager.process(q1c, q1cResults, storageManager->getReadStorage());

    std::list<std::string> a1cResults = {};
    REQUIRE(q1cResults == a1cResults);

    std::list<std::string> q1dResults;
    std::string q1d = "Select BOOLEAN such that Follows(1, 2)";
    queryManager.process(q1d, q1dResults, storageManager->getReadStorage());

    std::list<std::string> a1dResults = {"TRUE"};
    REQUIRE(q1dResults == a1dResults);

    std::list<std::string> q1eResults;
    std::string q1e = "Select BOOLEAN such that Follows(2, 1)";
    queryManager.process(q1e, q1eResults, storageManager->getReadStorage());

    std::list<std::string> a1eResults = {"FALSE"};
    REQUIRE(q1eResults == a1eResults);

    std::list<std::string> q1fResults;
    std::string q1f = "stmt s; assign a; Select s such that Follows(s, a)";
    queryManager.process(q1f, q1fResults, storageManager->getReadStorage());

    std::list<std::string> a1fResults = {"1", "3", "8", "9"};
    q1fResults.sort(compare_int_string);
    REQUIRE(q1fResults == a1fResults);

    std::list<std::string> q1gResults;
    std::string q1g = "stmt s; assign a; Select s such that follows(s, a)";
    queryManager.process(q1g, q1gResults, storageManager->getReadStorage());

    std::list<std::string> a1gResults = {"SyntaxError"};
    REQUIRE(q1gResults == a1gResults);

    // test FollowsT
    std::list<std::string> q2aResults;
    std::string q2a = "stmt s; Select s such that Follows*(1, s)";
    queryManager.process(q2a, q2aResults, storageManager->getReadStorage());

    std::list<std::string> a2aResults = {"2", "3", "7", "8", "14", "15"};
    q2aResults.sort(compare_int_string);
    REQUIRE(q2aResults == a2aResults);

    std::list<std::string> q2bResults;
    std::string q2b = "stmt s; Select s such that Follows*(s, 8)";
    queryManager.process(q2b, q2bResults, storageManager->getReadStorage());

    std::list<std::string> a2bResults = {"1", "2", "3", "7"};
    q2bResults.sort(compare_int_string);
    REQUIRE(q2bResults == a2bResults);

    std::list<std::string> q2cResults;
    std::string q2c = "Select BOOLEAN such that Follows*(_, 2)";
    queryManager.process(q2c, q2cResults, storageManager->getReadStorage());

    std::list<std::string> a2cResults = {"TRUE"};
    REQUIRE(q2cResults == a2cResults);

    std::list<std::string> q2dResults;
    std::string q2d = "stmt s; print p; Select s such that Follows*(p, 3)";
    queryManager.process(q2d, q2dResults, storageManager->getReadStorage());

    std::list<std::string> a2dResults = {};
    REQUIRE(q2dResults == a2dResults);

    std::list<std::string> q2eResults;
    std::string q2e = "assign a; while w; Select a such that Follows*(a, w)";
    queryManager.process(q2e, q2eResults, storageManager->getReadStorage());

    std::list<std::string> a2eResults = {"2", "7"};
    q2eResults.sort(compare_int_string);
    REQUIRE(q2eResults == a2eResults);

    std::list<std::string> q2fResults;
    std::string q2f = "if ifs; while w; Select ifs such that Follows*(ifs, w)";
    queryManager.process(q2f, q2fResults, storageManager->getReadStorage());

    std::list<std::string> a2fResults = {"3"};
    REQUIRE(q2fResults == a2fResults);

    std::list<std::string> q2gResults;
    std::string q2g = "stmt s; constant c; Select BOOLEAN such that Follows*(s, c)";
    queryManager.process(q2g, q2gResults, storageManager->getReadStorage());

    std::list<std::string> a2gResults = {"SemanticError"};
    REQUIRE(q2gResults == a2gResults);

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

    std::list<std::string> q3dResults;
    std::string q3d = "procedure proc; variable v; Select v such that Modifies(proc, v)";
    queryManager.process(q3d, q3dResults, storageManager->getReadStorage());

    std::list<std::string> a3dResults = {"a", "b", "c", "x", "y"};
    q3dResults.sort();
    REQUIRE(q3dResults == a3dResults);

    std::list<std::string> q3eResults;
    std::string q3e = "procedure proc; Select proc such that Modifies(proc, \"x\")";
    queryManager.process(q3e, q3eResults, storageManager->getReadStorage());

    std::list<std::string> a3eResults = {"test1"};
    REQUIRE(q3eResults == a3eResults);

    std::list<std::string> q3fResults;
    std::string q3f = "variable v; Select BOOLEAN such that Modifies(8, v)";
    queryManager.process(q3f, q3fResults, storageManager->getReadStorage());

    std::list<std::string> a3fResults = {"TRUE"};
    REQUIRE(q3fResults == a3fResults);

    std::list<std::string> q3gResults;
    std::string q3g = "variable v; if ifs; Select ifs.stmt# such that Modifies(ifs, v)";
    queryManager.process(q3g, q3gResults, storageManager->getReadStorage());

    std::list<std::string> a3gResults = {"3", "9"};
    q3gResults.sort(compare_int_string);
    REQUIRE(q3gResults == a3gResults);

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

    std::list<std::string> q4cResults;
    std::string q4c = "print p; Select p such that Parent(p, _)";
    queryManager.process(q4c, q4cResults, storageManager->getReadStorage());

    std::list<std::string> a4cResults = {};
    REQUIRE(q4cResults == a4cResults);

    std::list<std::string> q4dResults;
    std::string q4d = "procedure proc; Select BOOLEAN such that Parent(proc, 3)";
    queryManager.process(q4d, q4dResults, storageManager->getReadStorage());

    std::list<std::string> a4dResults = {"SemanticError"};
    q4dResults.sort();
    REQUIRE(q4dResults == a4dResults);

    std::list<std::string> q4eResults;
    std::string q4e = "statement s; Select s such that Parent(s, _)";
    queryManager.process(q4e, q4eResults, storageManager->getReadStorage());

    std::list<std::string> a4eResults = {"SyntaxError"};
    REQUIRE(q4eResults == a4eResults);

    std::list<std::string> q4fResults;
    std::string q4f = "if ifs; while w; Select <ifs, w> such that Parent(ifs, w)";
    queryManager.process(q4f, q4fResults, storageManager->getReadStorage());

    std::list<std::string> a4fResults = {};
    REQUIRE(q4fResults == a4fResults);

    std::list<std::string> q4gResults;
    std::string q4g = "stmt s; Select s such that Parent(_, _)";
    queryManager.process(q4g, q4gResults, storageManager->getReadStorage());

    std::list<std::string> a4gResults = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                                         "11", "12", "13", "14", "15", "16", "17", "18"};
    q4gResults.sort(compare_int_string);
    REQUIRE(q4gResults == a4gResults);

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

    std::list<std::string> q5cResults;
    std::string q5c = "read r; Select r such that Parent*(_, r)";
    queryManager.process(q5c, q5cResults, storageManager->getReadStorage());

    std::list<std::string> a5cResults = {};
    REQUIRE(q5cResults == a5cResults);

    std::list<std::string> q5dResults;
    std::string q5d = "Select BOOLEAN such that Parent*(3, 4)";
    queryManager.process(q5d, q5dResults, storageManager->getReadStorage());

    std::list<std::string> a5dResults = {"TRUE"};
    REQUIRE(q5dResults == a5dResults);

    std::list<std::string> q5eResults;
    std::string q5e = "stmt s; call cl; Select s such that Parent*(s, cl)";
    queryManager.process(q5e, q5eResults, storageManager->getReadStorage());

    std::list<std::string> a5eResults = {};
    REQUIRE(q5eResults == a5eResults);

    std::list<std::string> q5fResults;
    std::string q5f = "while w; Select w such that Parent*(w, _)";
    queryManager.process(q5f, q5fResults, storageManager->getReadStorage());

    std::list<std::string> a5fResults = {"8"};
    REQUIRE(q5fResults == a5fResults);

    std::list<std::string> q5gResults;
    std::string q5g = "if ifs; print p; Select ifs such that Parent*(ifs, p)";
    queryManager.process(q5g, q5gResults, storageManager->getReadStorage());

    std::list<std::string> a5gResults = {"3", "9"};
    q5gResults.sort(compare_int_string);
    REQUIRE(q5gResults == a5gResults);

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

    std::list<std::string> q6dResults;
    std::string q6d = "procedure proc; Select BOOLEAN such that Uses(proc, \"a\")";
    queryManager.process(q6d, q6dResults, storageManager->getReadStorage());

    std::list<std::string> a6dResults = {"TRUE"};
    REQUIRE(q6dResults == a6dResults);

    std::list<std::string> q6eResults;
    std::string q6e = "stmt s; call cl; Select s such that Uses(s, cl)";
    queryManager.process(q6e, q6eResults, storageManager->getReadStorage());

    std::list<std::string> a6eResults = {"SemanticError"};
    REQUIRE(q6eResults == a6eResults);

    std::list<std::string> q6fResults;
    std::string q6f = "while w; Select w such that Uses(w, _)";
    queryManager.process(q6f, q6fResults, storageManager->getReadStorage());

    std::list<std::string> a6fResults = {"8"};
    REQUIRE(q6fResults == a6fResults);

    std::list<std::string> q6gResults;
    std::string q6g = "procedure proc; Select proc such that Uses(proc, \"b\")";
    queryManager.process(q6g, q6gResults, storageManager->getReadStorage());

    std::list<std::string> a6gResults = {};
    REQUIRE(q6gResults == a6gResults);

    // test Calls
    std::list<std::string> q7aResults;
    std::string q7a = "call cl; Select cl";
    queryManager.process(q7a, q7aResults, storageManager->getReadStorage());

    std::list<std::string> a7aResults = {"15", "17"};
    q7aResults.sort(compare_int_string);
    REQUIRE(q7aResults == a7aResults);

    std::list<std::string> q7bResults;
    std::string q7b = "procedure proc; Select proc such that Calls(\"test2\", proc)";
    queryManager.process(q7b, q7bResults, storageManager->getReadStorage());

    std::list<std::string> a7bResults = {"test3"};
    REQUIRE(q7bResults == a7bResults);

    std::list<std::string> q7cResults;
    std::string q7c = "procedure proc; Select proc such that Calls(_, proc)";
    queryManager.process(q7c, q7cResults, storageManager->getReadStorage());

    std::list<std::string> a7cResults = {};
    REQUIRE(q7cResults == a7cResults);

    std::list<std::string> q7dResults;
    std::string q7d = "procedure proc; Select BOOLEAN such that Calls(proc, \"test4\")";
    queryManager.process(q7d, q7dResults, storageManager->getReadStorage());

    std::list<std::string> a7dResults = {"FALSE"};
    REQUIRE(q7dResults == a7dResults);

    std::list<std::string> q7eResults;
    std::string q7e = "Select BOOLEAN such that Calls(\"test1\", \"test2\")";
    queryManager.process(q7e, q7eResults, storageManager->getReadStorage());

    std::list<std::string> a7eResults = {"TRUE"};
    REQUIRE(q7eResults == a7eResults);

    std::list<std::string> q7fResults;
    std::string q7f = "while w; Select w such that Calls(w, _)";
    queryManager.process(q7f, q7fResults, storageManager->getReadStorage());

    std::list<std::string> a7fResults = {"SemanticError"};
    REQUIRE(q7fResults == a7fResults);

    std::list<std::string> q7gResults;
    std::string q7g = "procedure proc; Select proc.procName such that Calls(\"test2\", proc)";
    queryManager.process(q7g, q7gResults, storageManager->getReadStorage());

    std::list<std::string> a7gResults = {"test3"};
    REQUIRE(q7gResults == a7gResults);

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

    // test nextT
    std::list<std::string> q9aResults;
    std::string q9a = "stmt s; read r; Select s such that Next*(s, r)";
    queryManager.process(q9a, q9aResults, storageManager->getReadStorage());

    std::list<std::string> a9aResults = {};
    REQUIRE(q9aResults == a9aResults);

    std::list<std::string> q9bResults;
    std::string q9b = "stmt s; Select s such that Next*(11, s)";
    queryManager.process(q9b, q9bResults, storageManager->getReadStorage());

    std::list<std::string> a9bResults = {"8", "9", "10", "11", "12", "13", "14", "15"};
    q9bResults.sort(compare_int_string);
    REQUIRE(q9bResults == a9bResults);

    std::list<std::string> q9cResults;
    std::string q9c = "Select BOOLEAN such that Next*(9, _)";
    queryManager.process(q9c, q9cResults, storageManager->getReadStorage());

    std::list<std::string> a9cResults = {"TRUE"};
    REQUIRE(q9cResults == a9cResults);

    std::list<std::string> q9dResults;
    std::string q9d = "stmt s; print p; Select s such that Next*(p, 3)";
    queryManager.process(q9d, q9dResults, storageManager->getReadStorage());

    std::list<std::string> a9dResults = {};
    REQUIRE(q9dResults == a9dResults);

    std::list<std::string> q9eResults;
    std::string q9e = "assign a; while w; Select a such that Next*(a, w)";
    queryManager.process(q9e, q9eResults, storageManager->getReadStorage());

    std::list<std::string> a9eResults = {"2", "4", "6", "7", "11", "13"};
    q9eResults.sort(compare_int_string);
    REQUIRE(q9eResults == a9eResults);

    std::list<std::string> q9fResults;
    std::string q9f = "if ifs; while w; Select ifs such that Next*(ifs, w)";
    queryManager.process(q9f, q9fResults, storageManager->getReadStorage());

    std::list<std::string> a9fResults = {"3", "9"};
    q9fResults.sort(compare_int_string);
    REQUIRE(q9fResults == a9fResults);

    std::list<std::string> q9gResults;
    std::string q9g = "stmt s; constant c; Select BOOLEAN such that Next*(s, c)";
    queryManager.process(q9g, q9gResults, storageManager->getReadStorage());

    std::list<std::string> a9gResults = {"SemanticError"};
    REQUIRE(q9gResults == a9gResults);

    // test affects
    std::list<std::string> q10aResults;
    std::string q10a = "assign a; Select a such that Affects(a, 9)";
    queryManager.process(q10a, q10aResults, storageManager->getReadStorage());

    std::list<std::string> a10aResults = {};
    REQUIRE(q10aResults == a10aResults);

    std::list<std::string> q10bResults;
    std::string q10b = "stmt s; Select s such that Affects(s, _)";
    queryManager.process(q10b, q10bResults, storageManager->getReadStorage());

    std::list<std::string> a10bResults = {"2", "4", "6", "7", "11", "13"};
    q10bResults.sort(compare_int_string);
    REQUIRE(q10bResults == a10bResults);

    std::list<std::string> q10cResults;
    std::string q10c = "Select BOOLEAN such that Affects(2, _)";
    queryManager.process(q10c, q10cResults, storageManager->getReadStorage());

    std::list<std::string> a10cResults = {"TRUE"};
    REQUIRE(q10cResults == a10cResults);

    std::list<std::string> q10dResults;
    std::string q10d = "stmt s; assign a; Select s such that Affects(s, a)";
    queryManager.process(q10d, q10dResults, storageManager->getReadStorage());

    std::list<std::string> a10dResults = {"2", "4", "6", "7", "11", "13"};
    q10dResults.sort(compare_int_string);
    REQUIRE(q10dResults == a10dResults);

    std::list<std::string> q10eResults;
    std::string q10e = "assign a; while w; Select a such that Affects(a, w)";
    queryManager.process(q10e, q10eResults, storageManager->getReadStorage());

    std::list<std::string> a10eResults = {};
    REQUIRE(q10eResults == a10eResults);

    std::list<std::string> q10fResults;
    std::string q10f = "if ifs; while w; Select ifs such that Affects(ifs, w)";
    queryManager.process(q10f, q10fResults, storageManager->getReadStorage());

    std::list<std::string> a10fResults = {};
    REQUIRE(q10fResults == a10fResults);

    std::list<std::string> q10gResults;
    std::string q10g = "stmt s; constant c; Select BOOLEAN such that Affects(s, c)";
    queryManager.process(q10g, q10gResults, storageManager->getReadStorage());

    std::list<std::string> a10gResults = {"SemanticError"};
    REQUIRE(q10gResults == a10gResults);

    // test affectsT
    std::list<std::string> q11aResults;
    std::string q11a = "stmt s; Select s such that Affects*(_, s)";
    queryManager.process(q11a, q11aResults, storageManager->getReadStorage());

    std::list<std::string> a11aResults = {"4", "13", "14"};
    q11aResults.sort(compare_int_string);
    REQUIRE(q11aResults == a11aResults);

    std::list<std::string> q11bResults;
    std::string q11b = "stmt s; Select s such that Affects*(s, 8)";
    queryManager.process(q11b, q11bResults, storageManager->getReadStorage());

    std::list<std::string> a11bResults = {};
    q11bResults.sort(compare_int_string);
    REQUIRE(q11bResults == a11bResults);

    std::list<std::string> q11cResults;
    std::string q11c = "Select BOOLEAN such that Affects*(_, 11)";
    queryManager.process(q11c, q11cResults, storageManager->getReadStorage());

    std::list<std::string> a11cResults = {"FALSE"};
    REQUIRE(q11cResults == a11cResults);

    std::list<std::string> q11dResults;
    std::string q11d = "stmt s; print p; Select s such that Affects*(p, 3)";
    queryManager.process(q11d, q11dResults, storageManager->getReadStorage());

    std::list<std::string> a11dResults = {};
    REQUIRE(q11dResults == a11dResults);

    std::list<std::string> q11eResults;
    std::string q11e = "assign a; Select a such that Affects*(a, _)";
    queryManager.process(q11e, q11eResults, storageManager->getReadStorage());

    std::list<std::string> a11eResults = {"2", "4", "6", "7", "11", "13"};
    q11eResults.sort(compare_int_string);
    REQUIRE(q11eResults == a11eResults);

    std::list<std::string> q11fResults;
    std::string q11f = "if ifs; Select ifs such that Affects*(ifs, _)";
    queryManager.process(q11f, q11fResults, storageManager->getReadStorage());

    std::list<std::string> a11fResults = {};
    REQUIRE(q11fResults == a11fResults);

    std::list<std::string> q11gResults;
    std::string q11g = "stmt s; constant c; Select BOOLEAN such that Affects*(s, c)";
    queryManager.process(q11g, q11gResults, storageManager->getReadStorage());

    std::list<std::string> a11gResults = {"SemanticError"};
    REQUIRE(q11gResults == a11gResults);

    // test with
    std::list<std::string> q12aResults;
    std::string q12a = "constant c; Select BOOLEAN with 50 = c.value";
    queryManager.process(q12a, q12aResults, storageManager->getReadStorage());

    std::list<std::string> a12aResults = {"FALSE"};
    REQUIRE(q12aResults == a12aResults);

    std::list<std::string> q12bResults;
    std::string q12b = "call cl; Select BOOLEAN with 15 = cl.stmt#";
    queryManager.process(q12b, q12bResults, storageManager->getReadStorage());

    std::list<std::string> a12bResults = {"TRUE"};
    REQUIRE(q12bResults == a12bResults);

    std::list<std::string> q12cResults;
    std::string q12c = "procedure proc; Select proc with 1 = 1";
    queryManager.process(q12c, q12cResults, storageManager->getReadStorage());

    std::list<std::string> a12cResults = {"test1", "test2", "test3"};
    q12cResults.sort();
    REQUIRE(q12cResults == a12cResults);

    std::list<std::string> q12dResults;
    std::string q12d = "stmt s; read r; Select s with s.stmt# = r.stmt#";
    queryManager.process(q12d, q12dResults, storageManager->getReadStorage());

    std::list<std::string> a12dResults = {"1", "16", "18"};
    q12dResults.sort(compare_int_string);
    REQUIRE(q12dResults == a12dResults);

    std::list<std::string> q12eResults;
    std::string q12e = "read r; Select r with \"b\" = r.varName";
    queryManager.process(q12e, q12eResults, storageManager->getReadStorage());

    std::list<std::string> a12eResults = {"16"};
    REQUIRE(q12eResults == a12eResults);

    std::list<std::string> q12fResults;
    std::string q12f = "assign a; Select a with \"x\" = a.stmt#";
    queryManager.process(q12f, q12fResults, storageManager->getReadStorage());

    std::list<std::string> a12fResults = {"SemanticError"};
    REQUIRE(q12fResults == a12fResults);

    std::list<std::string> q12gResults;
    std::string q12g = "stmt s; assign a; Select s with s.stmt# = a.stmt#";
    queryManager.process(q12g, q12gResults, storageManager->getReadStorage());

    std::list<std::string> a12gResults = {"2", "4", "6", "7", "11", "13", "14"};
    q12gResults.sort(compare_int_string);
    REQUIRE(q12gResults == a12gResults);
}