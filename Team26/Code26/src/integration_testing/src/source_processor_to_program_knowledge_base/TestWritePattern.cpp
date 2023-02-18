#include "catch.hpp"
#include <filesystem>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include "source_processor/storage/interface/IStore.h"
#include "source_processor/storage/Store.h"
#include "source_processor/SourceManager.h"

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
    sourceManager.process(testFileName, store);
    auto readStorage = storageManager->getReadStorage();
    auto patternManager = readStorage->getPatternManager();

    std::vector<std::string> lhs_vector = {"x", "y", "z", "x"};
    std::vector<std::string> rhs_vector = {"5", "x*3", "x*y+x/y", "z"};
    std::unordered_map<int, int> index_stmt_map = {{0, 1}, {1, 2}, {2, 4}, {3, 5}};
    std::unordered_map<int, int> reversed_index_stmt_map = {{1, 0}, {2, 1}, {4, 2}, {5, 3}};;

    REQUIRE(patternManager->containsLhsVector("x"));
    REQUIRE(patternManager->containsLhsVector("y"));
    REQUIRE(patternManager->containsLhsVector("z"));
    REQUIRE(patternManager->getAllLhsPatternEntries() == lhs_vector);

    REQUIRE(patternManager->containsRhsVector("5"));
    REQUIRE(patternManager->containsRhsVector("x*3"));
    REQUIRE(patternManager->containsRhsVector("x*y+x/y"));
    REQUIRE(patternManager->containsRhsVector("z"));
    REQUIRE(patternManager->getAllRhsPatternEntries() == rhs_vector);

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
