#include "catch.hpp"
#include <filesystem>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include "source_processor/storage_writer/interface/IStore.h"
#include "source_processor/storage_writer/Store.h"
#include "source_processor/SourceManager.h"

TEST_CASE("Test insert entity for all managers") {

    std::string testFileName = "./testFile.txt";

    std::string testInput = "procedure test1 {\n"
                            "    x = 10;\n"
                            "    call test2;\n"
                            "    if (a > b) then {\n"
                            "        x = x + a;\n"
                            "    } else {\n"
                            "        x = x + b;\n"
                            "    }\n"
                            "    y = 3;\n"
                            "    while (y < 0) {\n"
                            "        print x;\n"
                            "        y = y - 1;\n"
                            "    }\n"
                            "}\n"
                            "\n"
                            "procedure test2 {\n"
                            "    read a;\n"
                            "    read b;\n"
                            "}";

    std::ofstream testFile;
    testFile.open (testFileName);
    testFile << testInput;
    testFile.close();

    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    SourceManager sourceManager;
    std::shared_ptr<IStore> store = std::make_shared<Store>(storageManager->getWriteStorage());
    sourceManager.process(testFileName, store, storageManager->getReadStorage());
    auto readStorage = storageManager->getReadStorage();

    // test AssignManager
    auto assignManager = readStorage->getAssignManager();
    std::unordered_set<int> assignSet = {1, 4, 5, 6, 9};
    auto storedAssignSet = assignManager->getAllEntitiesEntries();

    REQUIRE(assignManager->contains(1));
    REQUIRE(assignManager->contains(4));
    REQUIRE(assignManager->contains(5));
    REQUIRE(assignManager->contains(6));
    REQUIRE(assignManager->contains(9));
    REQUIRE(storedAssignSet.size() == assignSet.size());
    REQUIRE(storedAssignSet == assignSet);

    // test CallProcedureManager
    auto callProcedureManager = readStorage->getCallProcedureManager();
    std::unordered_set<std::string> callProcedureSet = {"test2"};
    auto storedCallProcedureSet = callProcedureManager->getAllEntitiesEntries();

    REQUIRE(callProcedureManager->contains("test2"));
    REQUIRE(storedCallProcedureSet.size() == callProcedureSet.size());
    REQUIRE(storedCallProcedureSet == callProcedureSet);

    // test CallStmtNoManager
    auto callStmtNoManager = readStorage->getCallStmtNoManager();
    std::unordered_set<int> callStmtNoSet = {2};
    auto storedCallStmtNoSet = callStmtNoManager->getAllEntitiesEntries();

    REQUIRE(callStmtNoManager->contains(2));
    REQUIRE(storedCallStmtNoSet.size() == callStmtNoSet.size());
    REQUIRE(storedCallStmtNoSet == callStmtNoSet);

    // test ConstantManager
    auto constantManager = readStorage->getConstantManager();
    std::unordered_set<int> constantSet = {0, 1, 3, 10};
    auto storedConstantSet = constantManager->getAllEntitiesEntries();

    REQUIRE(constantManager->contains(0));
    REQUIRE(constantManager->contains(1));
    REQUIRE(constantManager->contains(3));
    REQUIRE(constantManager->contains(10));
    REQUIRE(storedConstantSet.size() == constantSet.size());
    REQUIRE(storedConstantSet == constantSet);

    // test IfManager
    auto ifManager = readStorage->getIfManager();
    std::unordered_set<int> ifSet = {3};
    auto storedIfSet = ifManager->getAllEntitiesEntries();

    REQUIRE(ifManager->contains(3));
    REQUIRE(storedIfSet.size() == ifSet.size());
    REQUIRE(storedIfSet == ifSet);

    // test PrintStmtNoManager
    auto printStmtNoManager = readStorage->getPrintStmtNoManager();
    std::unordered_set<int> printStmtNoSet = {8};
    auto storedPrintStmtNoManagerSet = printStmtNoManager->getAllEntitiesEntries();

    REQUIRE(printStmtNoManager->contains(8));
    REQUIRE(storedPrintStmtNoManagerSet.size() == printStmtNoSet.size());
    REQUIRE(storedPrintStmtNoManagerSet == printStmtNoSet);

    // test PrintVariableManager
    auto printVariableManager = readStorage->getPrintVariableManager();
    std::unordered_set<std::string> printVariableSet = {"x"};
    auto storedPrintVariableSet = printVariableManager->getAllEntitiesEntries();

    REQUIRE(printVariableManager->contains("x"));
    REQUIRE(storedPrintVariableSet.size() == printVariableSet.size());
    REQUIRE(storedPrintVariableSet == printVariableSet);

    // test ProcedureManager
    auto procedureManager = readStorage->getProcedureManager();
    std::unordered_set<std::string> procedureSet = {"test1", "test2"};
    auto storedProcedureSet = procedureManager->getAllEntitiesEntries();

    REQUIRE(procedureManager->contains("test1"));
    REQUIRE(procedureManager->contains("test2"));
    REQUIRE(storedProcedureSet.size() == procedureSet.size());
    REQUIRE(storedProcedureSet == procedureSet);

    // test ReadStmtNoManager
    auto readStmtNoManager = readStorage->getReadStmtNoManager();
    std::unordered_set<int> readStmtNoSet = {10, 11};
    auto storedReadSet = readStmtNoManager->getAllEntitiesEntries();

    REQUIRE(readStmtNoManager->contains(10));
    REQUIRE(readStmtNoManager->contains(11));
    REQUIRE(storedReadSet.size() == readStmtNoSet.size());
    REQUIRE(storedReadSet == readStmtNoSet);

    // test ReadVariableManager
    auto readVariableManager = readStorage->getReadVariableManager();
    std::unordered_set<std::string> readVariableSet = {"a", "b"};
    auto storedReadVariableSet = readVariableManager->getAllEntitiesEntries();

    REQUIRE(readVariableManager->contains("a"));
    REQUIRE(readVariableManager->contains("b"));
    REQUIRE(storedReadVariableSet.size() == readVariableSet.size());
    REQUIRE(storedReadVariableSet == readVariableSet);

    // test StmtManager
    auto stmtManager = readStorage->getStmtManager();
    std::unordered_set<int> stmtSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    auto storedStmtSet = stmtManager->getAllEntitiesEntries();

    REQUIRE(stmtManager->contains(1));
    REQUIRE(stmtManager->contains(2));
    REQUIRE(stmtManager->contains(3));
    REQUIRE(stmtManager->contains(4));
    REQUIRE(stmtManager->contains(5));
    REQUIRE(stmtManager->contains(6));
    REQUIRE(stmtManager->contains(7));
    REQUIRE(stmtManager->contains(8));
    REQUIRE(stmtManager->contains(9));
    REQUIRE(stmtManager->contains(10));
    REQUIRE(stmtManager->contains(11));
    REQUIRE(storedStmtSet.size() == stmtSet.size());
    REQUIRE(storedStmtSet == stmtSet);

    // test VariableManager
    auto variableManager = readStorage->getVariableManager();
    std::unordered_set<std::string> variableSet = {"a", "b", "x", "y"};
    auto storedVariableSet = variableManager->getAllEntitiesEntries();

    REQUIRE(variableManager->contains("a"));
    REQUIRE(variableManager->contains("b"));
    REQUIRE(variableManager->contains("x"));
    REQUIRE(variableManager->contains("y"));
    REQUIRE(storedVariableSet.size() == variableSet.size());
    REQUIRE(storedVariableSet == variableSet);

    // test WhileManager
    auto whileManager = readStorage->getWhileManager();
    std::unordered_set<int> whileSet = {7};
    auto storedWhileSet = whileManager->getAllEntitiesEntries();

    REQUIRE(whileManager->contains(7));
    REQUIRE(storedWhileSet.size() == whileSet.size());
    REQUIRE(storedWhileSet == whileSet);

    std::filesystem::remove(testFileName);
}
