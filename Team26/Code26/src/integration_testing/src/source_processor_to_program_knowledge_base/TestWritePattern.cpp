#include "catch.hpp"
#include <filesystem>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>

#include "common/parser/ShuntingYardParser.h"
#include "source_processor/storage_writer/interface/IStore.h"
#include "source_processor/storage_writer/Store.h"
#include "source_processor/SourceManager.h"
#include "common/utils/SharedPointerComparator.h"

TEST_CASE("Test insert pattern") {
    std::string testInput = "procedure test1 {\n"
                            "    x = 5;\n"
                            "    y = x * 3;\n"
                            "    read z;\n"
                            "    z = x * y + x / y;\n"
                            "    x = z;\n"
                            "}";
    std::string testFileName = "./testFile.txt";

    std::ofstream testFile;
    testFile.open (testFileName);
    testFile << testInput;
    testFile.close();

    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    SourceManager sourceManager;
    std::shared_ptr<IStore> store = std::make_shared<Store>(storageManager->getWriteStorage());
    sourceManager.process(testFileName, store, storageManager->getReadStorage());
    auto readStorage = storageManager->getReadStorage();
    auto assignPatternManager = readStorage->getAssignPatternManager();

    std::vector<std::string> lhs_vector = {"x", "y", "z", "x"};

    auto node1 = ShuntingYardParser::parse("5");
    auto node2 = ShuntingYardParser::parse("x*3");
    auto node3 = ShuntingYardParser::parse("x*y+x/y");
    auto node4 = ShuntingYardParser::parse("z");
    std::vector<std::shared_ptr<ShuntNode>> rhs_vector = {node1, node2, node3, node4};

    std::unordered_map<int, int> index_stmt_map = {{0, 1}, {1, 2}, {2, 4}, {3, 5}};
    std::unordered_map<int, int> reversed_index_stmt_map = {{1, 0}, {2, 1}, {4, 2}, {5, 3}};

    REQUIRE(assignPatternManager->containsLhsVector("x"));
    REQUIRE(assignPatternManager->containsLhsVector("y"));
    REQUIRE(assignPatternManager->containsLhsVector("z"));
    REQUIRE(*(assignPatternManager->getAllLhsPatternEntries()) == lhs_vector);

    REQUIRE(assignPatternManager->containsRhsVector(node1));
    REQUIRE(assignPatternManager->containsRhsVector(node2));
    REQUIRE(assignPatternManager->containsRhsVector(node3));
    REQUIRE(assignPatternManager->containsRhsVector(node4));
    auto temp = assignPatternManager->getAllRhsPatternEntries();
    REQUIRE(std::equal(
            temp->begin(),
            temp->end(),
            rhs_vector.begin(),
            rhs_vector.end(),
            SharedPointerComparator<ShuntNode>()
    ));
    REQUIRE(assignPatternManager->containsIndexStmtMap(0, 1));
    REQUIRE(assignPatternManager->containsIndexStmtMap(1, 2));
    REQUIRE(assignPatternManager->containsIndexStmtMap(2, 4));
    REQUIRE(assignPatternManager->containsIndexStmtMap(3, 5));
    REQUIRE(assignPatternManager->getAllPatternEntries() == index_stmt_map);

    REQUIRE(assignPatternManager->containsReversedIndexStmtMap(1, 0));
    REQUIRE(assignPatternManager->containsReversedIndexStmtMap(2, 1));
    REQUIRE(assignPatternManager->containsReversedIndexStmtMap(4, 2));
    REQUIRE(assignPatternManager->containsReversedIndexStmtMap(5, 3));
    REQUIRE(assignPatternManager->getAllReversedPatternEntries() == reversed_index_stmt_map);

    std::filesystem::remove(testFileName);
}
