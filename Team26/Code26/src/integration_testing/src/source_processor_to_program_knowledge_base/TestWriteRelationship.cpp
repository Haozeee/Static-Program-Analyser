#include "catch.hpp"
#include <filesystem>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include "source_processor/storage_writer/interface/IStore.h"
#include "source_processor/storage_writer/Store.h"
#include "source_processor/SourceManager.h"

TEST_CASE("Test insert relationship for all managers") {
    std::string testInput = "procedure test1 {\n"
                            "    read a;\n"
                            "    x = 1;\n"
                            "    if (a > 0) then {\n"
                            "        x = x + 2;\n"
                            "        print x;\n"
                            "    } else {\n"
                            "        x = 0;\n"
                            "    }\n"
                            "    y = 2;\n"
                            "    while (y > 2) {\n"
                            "        if (x > 0) then {\n"
                            "            print x;\n"
                            "        } else {\n"
                            "            x = 1;\n"
                            "            print x;\n"
                            "        }\n"
                            "        y = y - 1;\n"
                            "    }\n"
                            "    y = x;\n"
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

    // test FollowsManager
    auto followsManager = readStorage->getFollowsManager();
    std::unordered_map<int, std::unordered_set<int>> follows_map = {{1, {2}}, {2, {3}}, {4, {5}}, {3, {7}}, {7, {8}},
                                                                    {8, {14}}, {9, {13}}, {11, {12}}};
    std::unordered_map<int, std::unordered_set<int>> reversed_follows_map = {{2, {1}}, {3, {2}}, {5, {4}},
                                                                             {7, {3}}, {8, {7}},  {14, {8}},
                                                                             {13, {9}}, {12, {11}}};

    REQUIRE(followsManager->containsMap(1, 2));
    REQUIRE(followsManager->containsMap(2, 3));
    REQUIRE(followsManager->containsMap(4, 5));
    REQUIRE(followsManager->containsMap(3, 7));
    REQUIRE(followsManager->containsMap(7, 8));
    REQUIRE(followsManager->containsMap(8, 14));
    REQUIRE(followsManager->containsMap(9, 13));
    REQUIRE(followsManager->containsMap(11, 12));
    REQUIRE(followsManager->getAllRelationshipEntries() == follows_map);

    REQUIRE(followsManager->containsReversedMap(2, 1));
    REQUIRE(followsManager->containsReversedMap(3, 2));
    REQUIRE(followsManager->containsReversedMap(5, 4));
    REQUIRE(followsManager->containsReversedMap(7, 3));
    REQUIRE(followsManager->containsReversedMap(8, 7));
    REQUIRE(followsManager->containsReversedMap(14, 8));
    REQUIRE(followsManager->containsReversedMap(13, 9));
    REQUIRE(followsManager->containsReversedMap(12, 11));
    REQUIRE(followsManager->getAllReversedRelationshipEntries() == reversed_follows_map);

    // test FollowsTManager
    auto followsTManager = readStorage->getFollowsTManager();
    std::unordered_map<int, std::unordered_set<int>> followsT_map = {{1, {2, 3, 7, 8, 14}}, {2, {3, 7, 8, 14}},
                                                                     {4, {5}}, {3, {7, 8 ,14}}, {7, {8, 14}},
                                                                     {8, {14}}, {9, {13}}, {11, {12}}};
    std::unordered_map<int, std::unordered_set<int>> reversed_followsT_map = {{8, {1, 2, 3, 7}}, {14, {1, 2, 3, 7, 8}},
                                                                              {3, {1, 2}}, {5, {4}}, {12, {11}},
                                                                              {7, {1, 2, 3}}, {13, {9}}, {2, {1}}};

    REQUIRE(followsTManager->containsMap(1, 2));
    REQUIRE(followsTManager->containsMap(1, 3));
    REQUIRE(followsTManager->containsMap(1, 7));
    REQUIRE(followsTManager->containsMap(1, 8));
    REQUIRE(followsTManager->containsMap(1, 14));
    REQUIRE(followsTManager->containsMap(2, 3));
    REQUIRE(followsTManager->containsMap(2, 7));
    REQUIRE(followsTManager->containsMap(2, 8));
    REQUIRE(followsTManager->containsMap(2, 14));
    REQUIRE(followsTManager->containsMap(4, 5));
    REQUIRE(followsTManager->containsMap(3, 7));
    REQUIRE(followsTManager->containsMap(3, 8));
    REQUIRE(followsTManager->containsMap(3, 14));
    REQUIRE(followsTManager->containsMap(7, 8));
    REQUIRE(followsTManager->containsMap(7, 14));
    REQUIRE(followsTManager->containsMap(8, 14));
    REQUIRE(followsTManager->containsMap(9, 13));
    REQUIRE(followsTManager->containsMap(11, 12));
    REQUIRE(followsTManager->getAllRelationshipEntries() == followsT_map);

    REQUIRE(followsTManager->containsReversedMap(2, 1));
    REQUIRE(followsTManager->containsReversedMap(3, 1));
    REQUIRE(followsTManager->containsReversedMap(7, 1));
    REQUIRE(followsTManager->containsReversedMap(8, 1));
    REQUIRE(followsTManager->containsReversedMap(14, 1));
    REQUIRE(followsTManager->containsReversedMap(3, 2));
    REQUIRE(followsTManager->containsReversedMap(7, 2));
    REQUIRE(followsTManager->containsReversedMap(8, 2));
    REQUIRE(followsTManager->containsReversedMap(14, 2));
    REQUIRE(followsTManager->containsReversedMap(5, 4));
    REQUIRE(followsTManager->containsReversedMap(7, 3));
    REQUIRE(followsTManager->containsReversedMap(8, 3));
    REQUIRE(followsTManager->containsReversedMap(14, 3));
    REQUIRE(followsTManager->containsReversedMap(8, 7));
    REQUIRE(followsTManager->containsReversedMap(14, 7));
    REQUIRE(followsTManager->containsReversedMap(14, 8));
    REQUIRE(followsTManager->containsReversedMap(13, 9));
    REQUIRE(followsTManager->containsReversedMap(12, 11));
    REQUIRE(followsTManager->getAllReversedRelationshipEntries() == reversed_followsT_map);

    //  test ModifiesPManager
    auto modifiesPManager = readStorage->getModifiesPManager();

    std::unordered_map<std::string, std::unordered_set<std::string>> modifiesP_map = {{"test1", {"a", "x", "y"}}};
    std::unordered_map<std::string, std::unordered_set<std::string>> reversed_modifiesP_map = {{"a", {"test1"}},
                                                                                               {"x", {"test1"}},
                                                                                               {"y", {"test1"}}};

    REQUIRE(modifiesPManager->containsMap("test1", "a"));
    REQUIRE(modifiesPManager->containsMap("test1", "x"));
    REQUIRE(modifiesPManager->containsMap("test1", "y"));
    REQUIRE(modifiesPManager->getAllRelationshipEntries() == modifiesP_map);

    REQUIRE(modifiesPManager->containsReversedMap("a", "test1"));
    REQUIRE(modifiesPManager->containsReversedMap("x", "test1"));
    REQUIRE(modifiesPManager->containsReversedMap("y", "test1"));
    REQUIRE(modifiesPManager->getAllReversedRelationshipEntries() == reversed_modifiesP_map);

    // test ModifiesSManager
    auto modifiesSManager = readStorage->getModifiesSManager();

    std::unordered_map<int, std::unordered_set<std::string>> modifiesS_map = {{1, {"a"}}, {2, {"x"}}, {3, {"x"}},
                                                                              {4, {"x"}}, {6, {"x"}}, {7, {"y"}},
                                                                              {8, {"x", "y"}}, {9, {"x"}}, {11, {"x"}},
                                                                              {13, {"y"}}, {14, {"y"}}};
    std::unordered_map<std::string, std::unordered_set<int>> reversed_modifiesS_map = {{"a", {1}},
                                                                                       {"x", {2, 3, 4, 6, 8, 9, 11}},
                                                                                       {"y", {7, 8, 13, 14}}};

    REQUIRE(modifiesSManager->containsMap(1,"a"));
    REQUIRE(modifiesSManager->containsMap(2,"x"));
    REQUIRE(modifiesSManager->containsMap(3,"x"));
    REQUIRE(modifiesSManager->containsMap(4,"x"));
    REQUIRE(modifiesSManager->containsMap(6,"x"));
    REQUIRE(modifiesSManager->containsMap(7,"y"));
    REQUIRE(modifiesSManager->containsMap(8,"x"));
    REQUIRE(modifiesSManager->containsMap(8,"y"));
    REQUIRE(modifiesSManager->containsMap(9,"x"));
    REQUIRE(modifiesSManager->containsMap(11,"x"));
    REQUIRE(modifiesSManager->containsMap(13,"y"));
    REQUIRE(modifiesSManager->containsMap(14,"y"));
    REQUIRE(modifiesSManager->getAllRelationshipEntries() == modifiesS_map);

    REQUIRE(modifiesSManager->containsReversedMap("a", 1));
    REQUIRE(modifiesSManager->containsReversedMap("x", 2));
    REQUIRE(modifiesSManager->containsReversedMap("x", 3));
    REQUIRE(modifiesSManager->containsReversedMap("x", 4));
    REQUIRE(modifiesSManager->containsReversedMap("x", 6));
    REQUIRE(modifiesSManager->containsReversedMap("x", 8));
    REQUIRE(modifiesSManager->containsReversedMap("x", 9));
    REQUIRE(modifiesSManager->containsReversedMap("x", 11));
    REQUIRE(modifiesSManager->containsReversedMap("y", 7));
    REQUIRE(modifiesSManager->containsReversedMap("y", 8));
    REQUIRE(modifiesSManager->containsReversedMap("y", 13));
    REQUIRE(modifiesSManager->containsReversedMap("y", 14));
    REQUIRE(modifiesSManager->getAllReversedRelationshipEntries() == reversed_modifiesS_map);

    // test ParentManager
    auto parentManager = readStorage->getParentManager();
    std::unordered_map<int, std::unordered_set<int>> parent_map = {{3, {4, 5, 6}}, {8, {9, 13}}, {9, {10, 11, 12}}};
    std::unordered_map<int, std::unordered_set<int>> reversed_parent_map = {{4, {3}}, {5, {3}}, {6, {3}},
                                                                            {9, {8}}, {13, {8}},  {10, {9}},
                                                                            {11, {9}}, {12, {9}}};

    REQUIRE(parentManager->containsMap(3, 4));
    REQUIRE(parentManager->containsMap(3, 5));
    REQUIRE(parentManager->containsMap(3, 6));
    REQUIRE(parentManager->containsMap(8, 9));
    REQUIRE(parentManager->containsMap(8, 13));
    REQUIRE(parentManager->containsMap(9, 10));
    REQUIRE(parentManager->containsMap(9, 11));
    REQUIRE(parentManager->containsMap(9, 12));
    REQUIRE(parentManager->getAllRelationshipEntries() == parent_map);

    REQUIRE(parentManager->containsReversedMap(4, 3));
    REQUIRE(parentManager->containsReversedMap(5, 3));
    REQUIRE(parentManager->containsReversedMap(6, 3));
    REQUIRE(parentManager->containsReversedMap(9, 8));
    REQUIRE(parentManager->containsReversedMap(13, 8));
    REQUIRE(parentManager->containsReversedMap(10, 9));
    REQUIRE(parentManager->containsReversedMap(11, 9));
    REQUIRE(parentManager->containsReversedMap(12, 9));
    REQUIRE(parentManager->getAllReversedRelationshipEntries() == reversed_parent_map);


    // test ParentTManager
    auto parentTManager = readStorage->getParentTManager();
    std::unordered_map<int, std::unordered_set<int>> parentT_map = {{3, {4, 5, 6}}, {8, {9, 10, 11, 12, 13}},
                                                                    {9, {10, 11, 12}}};
    std::unordered_map<int, std::unordered_set<int>> reversed_parentT_map = {{4, {3}}, {5, {3}}, {6, {3}}, {9, {8}},
                                                                             {13, {8}},  {10, {8, 9}}, {11, {8, 9}},
                                                                             {12, {8, 9}}};

    REQUIRE(parentTManager->containsMap(3, 4));
    REQUIRE(parentTManager->containsMap(3, 5));
    REQUIRE(parentTManager->containsMap(3, 6));
    REQUIRE(parentTManager->containsMap(8, 9));
    REQUIRE(parentTManager->containsMap(8, 10));
    REQUIRE(parentTManager->containsMap(8, 11));
    REQUIRE(parentTManager->containsMap(8, 12));
    REQUIRE(parentTManager->containsMap(8, 13));
    REQUIRE(parentTManager->containsMap(9, 10));
    REQUIRE(parentTManager->containsMap(9, 11));
    REQUIRE(parentTManager->containsMap(9, 12));
    REQUIRE(parentTManager->getAllRelationshipEntries() == parentT_map);

    REQUIRE(parentTManager->containsReversedMap(4, 3));
    REQUIRE(parentTManager->containsReversedMap(5, 3));
    REQUIRE(parentTManager->containsReversedMap(6, 3));
    REQUIRE(parentTManager->containsReversedMap(9, 8));
    REQUIRE(parentTManager->containsReversedMap(10, 8));
    REQUIRE(parentTManager->containsReversedMap(11, 8));
    REQUIRE(parentTManager->containsReversedMap(12, 8));
    REQUIRE(parentTManager->containsReversedMap(13, 8));
    REQUIRE(parentTManager->containsReversedMap(10, 9));
    REQUIRE(parentTManager->containsReversedMap(11, 9));
    REQUIRE(parentTManager->containsReversedMap(12, 9));
    REQUIRE(parentTManager->getAllReversedRelationshipEntries() == reversed_parentT_map);

    // test UsesPManager
    auto usesPManager = readStorage->getUsesPManager();

    std::unordered_map<std::string, std::unordered_set<std::string>> usesP_map = {{"test1", {"a", "x", "y"}}};
    std::unordered_map<std::string, std::unordered_set<std::string>> reversed_usesP_map = {{"a", {"test1"}},
                                                                                           {"x", {"test1"}},
                                                                                           {"y", {"test1"}}};

    REQUIRE(usesPManager->containsMap("test1", "a"));
    REQUIRE(usesPManager->containsMap("test1", "x"));
    REQUIRE(usesPManager->containsMap("test1", "y"));
    REQUIRE(usesPManager->getAllRelationshipEntries() == usesP_map);

    REQUIRE(usesPManager->containsReversedMap("a", "test1"));
    REQUIRE(usesPManager->containsReversedMap("x", "test1"));
    REQUIRE(usesPManager->containsReversedMap("y", "test1"));
    REQUIRE(usesPManager->getAllReversedRelationshipEntries() == reversed_usesP_map);

    // test UsesSManager
    auto usesSManager = readStorage->getUsesSManager();

    std::unordered_map<int, std::unordered_set<std::string>> usesS_map = {{3, {"a", "x"}}, {4, {"x"}}, {5, {"x"}},
                                                                          {8, {"x", "y"}}, {9, {"x"}}, {10, {"x"}},
                                                                          {12, {"x"}}, {13, {"y"}}, {14, {"x"}}};
    std::unordered_map<std::string, std::unordered_set<int>> reversed_usesS_map = {{"a", {3}},
                                                                                   {"x", {3, 4, 5, 8, 9, 10, 12, 14}},
                                                                                   {"y", {8, 13}}};

    REQUIRE(usesSManager->containsMap(3, "a"));
    REQUIRE(usesSManager->containsMap(3, "x"));
    REQUIRE(usesSManager->containsMap(4, "x"));
    REQUIRE(usesSManager->containsMap(5, "x"));
    REQUIRE(usesSManager->containsMap(8, "x"));
    REQUIRE(usesSManager->containsMap(8, "y"));
    REQUIRE(usesSManager->containsMap(9, "x"));
    REQUIRE(usesSManager->containsMap(10, "x"));
    REQUIRE(usesSManager->containsMap(12, "x"));
    REQUIRE(usesSManager->containsMap(13, "y"));
    REQUIRE(usesSManager->containsMap(14, "x"));
    REQUIRE(usesSManager->getAllRelationshipEntries() == usesS_map);


    REQUIRE(usesSManager->containsReversedMap("a", 3));
    REQUIRE(usesSManager->containsReversedMap("x", 3));
    REQUIRE(usesSManager->containsReversedMap("x", 4));
    REQUIRE(usesSManager->containsReversedMap("x", 5));
    REQUIRE(usesSManager->containsReversedMap("x", 8));
    REQUIRE(usesSManager->containsReversedMap("y", 8));
    REQUIRE(usesSManager->containsReversedMap("x", 9));
    REQUIRE(usesSManager->containsReversedMap("x", 10));
    REQUIRE(usesSManager->containsReversedMap("x", 12));
    REQUIRE(usesSManager->containsReversedMap("y", 13));
    REQUIRE(usesSManager->containsReversedMap("x", 14));
    REQUIRE(usesSManager->getAllReversedRelationshipEntries() == reversed_usesS_map);

    std::filesystem::remove(testFileName);
}
