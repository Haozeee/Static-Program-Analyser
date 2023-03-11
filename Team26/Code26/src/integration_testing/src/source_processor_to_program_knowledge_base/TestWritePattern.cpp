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
    auto patternManager = readStorage->getPatternManager();

    std::vector<std::string> lhs_vector = {"x", "y", "z", "x"};

    auto node1 = ShuntingYardParser::parse("5");
    auto node2 = ShuntingYardParser::parse("x*3");
    auto node3 = ShuntingYardParser::parse("x*y+x/y");
    auto node4 = ShuntingYardParser::parse("z");
    std::vector<const std::shared_ptr<ShuntNode>> rhs_vector = {node1, node2, node3, node4};

    std::unordered_map<int, int> index_stmt_map = {{0, 1}, {1, 2}, {2, 4}, {3, 5}};
    std::unordered_map<int, int> reversed_index_stmt_map = {{1, 0}, {2, 1}, {4, 2}, {5, 3}};

    REQUIRE(patternManager->containsLhsVector("x"));
    REQUIRE(patternManager->containsLhsVector("y"));
    REQUIRE(patternManager->containsLhsVector("z"));
    REQUIRE(patternManager->getAllLhsPatternEntries() == lhs_vector);

    REQUIRE(patternManager->containsRhsVector(node1));
    REQUIRE(patternManager->containsRhsVector(node2));
    REQUIRE(patternManager->containsRhsVector(node3));
    REQUIRE(patternManager->containsRhsVector(node4));
    auto temp = patternManager->getAllRhsPatternEntries();
    REQUIRE(std::equal(
            temp.begin(),
            temp.end(),
            rhs_vector.begin(),
            rhs_vector.end(),
            SharedPointerComparator<ShuntNode>()
    ));
    REQUIRE(patternManager->containsIndexStmtMap(0, 1));
    REQUIRE(patternManager->containsIndexStmtMap(1, 2));
    REQUIRE(patternManager->containsIndexStmtMap(2, 4));
    REQUIRE(patternManager->containsIndexStmtMap(3, 5));
    REQUIRE(patternManager->getAllPatternEntries() == index_stmt_map);

    REQUIRE(patternManager->containsReversedIndexStmtMap(1, 0));
    REQUIRE(patternManager->containsReversedIndexStmtMap(2, 1));
    REQUIRE(patternManager->containsReversedIndexStmtMap(4, 2));
    REQUIRE(patternManager->containsReversedIndexStmtMap(5, 3));
    REQUIRE(patternManager->getAllReversedPatternEntries() == reversed_index_stmt_map);

    std::filesystem::remove(testFileName);
}
