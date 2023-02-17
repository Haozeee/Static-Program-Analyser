#include "catch.hpp"
#include <filesystem>
#include <string>
#include <utility>
#include "source_processor/storage/interface/IStore.h"
#include "source_processor/storage/Store.h"
#include "source_processor/SourceManager.h"

TEST_CASE("Test insert pattern") {
    std::string cwd = std::filesystem::current_path().string();
    std::string word = "/cmake-build-debug";
    size_t pos = cwd.find(word);
    if (pos != std::string::npos) {
        cwd.erase(pos, word.length());
    }

    const std::string &filename =
            cwd + "/src/source_processor_to_program_knowledge_base/source_pattern_insert.txt";

    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    SourceManager sourceManager;
    std::shared_ptr<IStore> store = std::make_shared<Store>(storageManager->getWriteStorage());
    sourceManager.process(filename, store);
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
}
