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

    REQUIRE(assignManager->contains(1));
    REQUIRE(assignManager->contains(4));
    REQUIRE(assignManager->contains(5));
    REQUIRE(assignManager->contains(6));
    REQUIRE(assignManager->contains(9));
    REQUIRE(assignManager->getAllEntitiesEntries() == assignSet);

    // test CallStmtNoManager
    auto callManager = readStorage->getCallManager();
    std::unordered_set<int> callSet = {2};

    REQUIRE(callManager->contains(2));
    REQUIRE(callManager->getAllEntitiesEntries() == callSet);

    // test ConstantManager
    auto constantManager = readStorage->getConstantManager();
    std::unordered_set<int> constantSet = {0, 1, 3, 10};

    REQUIRE(constantManager->contains(0));
    REQUIRE(constantManager->contains(1));
    REQUIRE(constantManager->contains(3));
    REQUIRE(constantManager->contains(10));
    REQUIRE(constantManager->getAllEntitiesEntries() == constantSet);

    // test IfManager
    auto ifManager = readStorage->getIfManager();
    std::unordered_set<int> ifSet = {3};

    REQUIRE(ifManager->contains(3));
    REQUIRE(ifManager->getAllEntitiesEntries() == ifSet);

    // test PrintManager
    auto printManager = readStorage->getPrintStmtNoManager();
    std::unordered_set<int> printSet = {8};

    REQUIRE(printManager->contains(8));
    REQUIRE(printManager->getAllEntitiesEntries() == printSet);

    // test ProcedureManager
    auto procedureManager = readStorage->getProcedureManager();
    std::unordered_set<std::string> procedureSet = {"test1", "test2"};

    REQUIRE(procedureManager->contains("test1"));
    REQUIRE(procedureManager->contains("test2"));
    REQUIRE(procedureManager->getAllEntitiesEntries() == procedureSet);

    // test ReadManager
    auto readManager = readStorage->getReadStmtNoManager();
    std::unordered_set<int> readSet = {10, 11};

    REQUIRE(readManager->contains(10));
    REQUIRE(readManager->contains(11));
    REQUIRE(readManager->getAllEntitiesEntries() == readSet);

    // test StmtManager
    auto stmtManager = readStorage->getStmtManager();
    std::unordered_set<int> stmtSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

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
    REQUIRE(stmtManager->getAllEntitiesEntries() == stmtSet);

    // test VariableManager
    auto variableManager = readStorage->getVariableManager();
    std::unordered_set<std::string> variableSet = {"a", "b", "x", "y"};

    REQUIRE(variableManager->contains("a"));
    REQUIRE(variableManager->contains("b"));
    REQUIRE(variableManager->contains("x"));
    REQUIRE(variableManager->contains("y"));
    REQUIRE(variableManager->getAllEntitiesEntries() == variableSet);

    // test WhileManager
    auto whileManager = readStorage->getWhileManager();
    std::unordered_set<int> whileSet = {7};

    REQUIRE(whileManager->contains(7));
    REQUIRE(whileManager->getAllEntitiesEntries() == whileSet);

    std::filesystem::remove(testFileName);
}
