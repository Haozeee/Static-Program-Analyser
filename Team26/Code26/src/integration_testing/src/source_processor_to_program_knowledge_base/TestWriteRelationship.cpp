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
                            "    call test2;\n"
                            "}\n"
                            "\n"
                            "procedure test2 {\n"
                            "    read b;\n"
                            "    call test3;\n"
                            "}\n"
                            "\n"
                            "procedure test3 {\n"
                            "    read c;\n"
                            "}";

    std::string testFileName = "./testFile.txt";

    std::ofstream testFile;
    testFile.open (testFileName);
    testFile << testInput;
    testFile.close();

    std::unique_ptr<StorageManager> storageManager = std::make_unique<StorageManager>();
    SourceManager sourceManager;
    std::shared_ptr<IStore> store = std::make_shared<Store>(storageManager->getWriteStorage(), storageManager->getReadStorage());
    sourceManager.process(testFileName, store);
    auto readStorage = storageManager->getReadStorage();

    // test FollowsManager
    auto followsManager = readStorage->getFollowsManager();
    std::unordered_map<int, std::unordered_set<int>> follows_map = {{1, {2}}, {2, {3}}, {4, {5}}, {3, {7}}, {7, {8}},
                                                                    {8, {14}}, {9, {13}}, {11, {12}},
                                                                    {14, {15}}, {16, {17}}};

    std::unordered_map<int, std::unordered_set<int>> reversed_follows_map = {{2, {1}}, {3, {2}}, {5, {4}},
                                                                             {7, {3}}, {8, {7}},  {14, {8}},
                                                                             {13, {9}}, {12, {11}}, {15, {14}},
                                                                             {17, {16}}};

    auto storedFollowsMap = followsManager->getAllRelationshipEntries();
    auto storedReversedFollowsMap = followsManager->getAllReversedRelationshipEntries();

    REQUIRE(followsManager->containsMap(1, 2));
    REQUIRE(followsManager->containsMap(2, 3));
    REQUIRE(followsManager->containsMap(4, 5));
    REQUIRE(followsManager->containsMap(3, 7));
    REQUIRE(followsManager->containsMap(7, 8));
    REQUIRE(followsManager->containsMap(8, 14));
    REQUIRE(followsManager->containsMap(9, 13));
    REQUIRE(followsManager->containsMap(11, 12));
    REQUIRE(followsManager->containsMap(14, 15));
    REQUIRE(followsManager->containsMap(16, 17));
    REQUIRE(storedFollowsMap.size() == follows_map.size());
    REQUIRE(storedFollowsMap == follows_map);

    REQUIRE(followsManager->containsReversedMap(2, 1));
    REQUIRE(followsManager->containsReversedMap(3, 2));
    REQUIRE(followsManager->containsReversedMap(5, 4));
    REQUIRE(followsManager->containsReversedMap(7, 3));
    REQUIRE(followsManager->containsReversedMap(8, 7));
    REQUIRE(followsManager->containsReversedMap(14, 8));
    REQUIRE(followsManager->containsReversedMap(13, 9));
    REQUIRE(followsManager->containsReversedMap(12, 11));
    REQUIRE(followsManager->containsReversedMap(15, 14));
    REQUIRE(followsManager->containsReversedMap(17, 16));
    REQUIRE(storedReversedFollowsMap.size() == reversed_follows_map.size());
    REQUIRE(storedReversedFollowsMap == reversed_follows_map);

    // test FollowsTManager
    auto followsTManager = readStorage->getFollowsTManager();
    std::unordered_map<int, std::unordered_set<int>> followsT_map = {{1, {2, 3, 7, 8, 14, 15}}, {2, {3, 7, 8, 14, 15}},
                                                                     {4, {5}}, {3, {7, 8 ,14, 15}}, {7, {8, 14, 15}},
                                                                     {8, {14, 15}}, {9, {13}}, {11, {12}},
                                                                     {14, {15}}, {16, {17}}};

    std::unordered_map<int, std::unordered_set<int>> reversed_followsT_map = {{8, {1, 2, 3, 7}}, {14, {1, 2, 3, 7, 8}},
                                                                              {3, {1, 2}}, {5, {4}}, {12, {11}},
                                                                              {7, {1, 2, 3}}, {13, {9}}, {2, {1}},
                                                                              {15, {1, 2, 3, 7, 8, 14}}, {17, {16}}};

    auto storedFollowsTMap = followsTManager->getAllRelationshipEntries();
    auto storedReversedFollowsTMap = followsTManager->getAllReversedRelationshipEntries();

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
    REQUIRE(followsTManager->containsMap(1, 15));
    REQUIRE(followsTManager->containsMap(2, 15));
    REQUIRE(followsTManager->containsMap(3, 15));
    REQUIRE(followsTManager->containsMap(7, 15));
    REQUIRE(followsTManager->containsMap(8, 15));
    REQUIRE(followsTManager->containsMap(14, 15));
    REQUIRE(followsTManager->containsMap(16, 17));
    REQUIRE(storedFollowsTMap.size() == followsT_map.size());
    REQUIRE(storedFollowsTMap == followsT_map);

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
    REQUIRE(followsTManager->containsReversedMap(15, 1));
    REQUIRE(followsTManager->containsReversedMap(15, 2));
    REQUIRE(followsTManager->containsReversedMap(15, 3));
    REQUIRE(followsTManager->containsReversedMap(15, 7));
    REQUIRE(followsTManager->containsReversedMap(15, 8));
    REQUIRE(followsTManager->containsReversedMap(15, 14));
    REQUIRE(followsTManager->containsReversedMap(17, 16));
    REQUIRE(storedReversedFollowsTMap.size() == reversed_followsT_map.size());
    REQUIRE(storedReversedFollowsTMap == reversed_followsT_map);

    //  test ModifiesPManager
    auto modifiesPManager = readStorage->getModifiesPManager();

    std::unordered_map<std::string, std::unordered_set<std::string>> modifiesP_map = {{"test1", {"a", "x",
                                                                                                 "y", "b", "c"}},
                                                                                      {"test2", {"b", "c"}},
                                                                                      {"test3", {"c"}}};

    std::unordered_map<std::string, std::unordered_set<std::string>> reversed_modifiesP_map = {{"a", {"test1"}},
                                                                                               {"x", {"test1"}},
                                                                                               {"y", {"test1"}},
                                                                                               {"b", {"test1",
                                                                                                      "test2"}},
                                                                                               {"c", {"test1",
                                                                                                      "test2",
                                                                                                      "test3"}}};

    auto storedModifiesPMap = modifiesPManager->getAllRelationshipEntries();
    auto storedReversedModifiesPMap = modifiesPManager->getAllReversedRelationshipEntries();

    REQUIRE(modifiesPManager->containsMap("test1", "a"));
    REQUIRE(modifiesPManager->containsMap("test1", "b"));
    REQUIRE(modifiesPManager->containsMap("test1", "c"));
    REQUIRE(modifiesPManager->containsMap("test1", "x"));
    REQUIRE(modifiesPManager->containsMap("test1", "y"));
    REQUIRE(modifiesPManager->containsMap("test2", "b"));
    REQUIRE(modifiesPManager->containsMap("test2", "c"));
    REQUIRE(modifiesPManager->containsMap("test3", "c"));
    REQUIRE(storedModifiesPMap.size() == modifiesP_map.size());
    REQUIRE(storedModifiesPMap == modifiesP_map);

    REQUIRE(modifiesPManager->containsReversedMap("a", "test1"));
    REQUIRE(modifiesPManager->containsReversedMap("x", "test1"));
    REQUIRE(modifiesPManager->containsReversedMap("y", "test1"));
    REQUIRE(modifiesPManager->containsReversedMap("b", "test2"));
    REQUIRE(modifiesPManager->containsReversedMap("c", "test2"));
    REQUIRE(modifiesPManager->containsReversedMap("c", "test1"));
    REQUIRE(modifiesPManager->containsReversedMap("c", "test2"));
    REQUIRE(modifiesPManager->containsReversedMap("c", "test3"));
    REQUIRE(storedReversedModifiesPMap.size() == reversed_modifiesP_map.size());
    REQUIRE(storedReversedModifiesPMap == reversed_modifiesP_map);

    // test ModifiesSManager
    auto modifiesSManager = readStorage->getModifiesSManager();

    std::unordered_map<int, std::unordered_set<std::string>> modifiesS_map = {{1, {"a"}}, {2, {"x"}}, {3, {"x"}},
                                                                              {4, {"x"}}, {6, {"x"}}, {7, {"y"}},
                                                                              {8, {"x", "y"}}, {9, {"x"}}, {11, {"x"}},
                                                                              {13, {"y"}}, {14, {"y"}},
                                                                              {15, {"b", "c"}}, {16, {"b"}},
                                                                              {17, {"c"}}, {18, {"c"}}};

    std::unordered_map<std::string, std::unordered_set<int>> reversed_modifiesS_map = {{"a", {1}},
                                                                                       {"x", {2, 3, 4, 6, 8, 9, 11}},
                                                                                       {"y", {7, 8, 13, 14}},
                                                                                       {"b", {15, 16}},
                                                                                       {"c", {15, 17, 18}}};

    auto storedModifiesSMap = modifiesSManager->getAllRelationshipEntries();
    auto storedReversedModifiesSMap = modifiesSManager->getAllReversedRelationshipEntries();

    REQUIRE(modifiesSManager->containsMap(1, "a"));
    REQUIRE(modifiesSManager->containsMap(2, "x"));
    REQUIRE(modifiesSManager->containsMap(3, "x"));
    REQUIRE(modifiesSManager->containsMap(4, "x"));
    REQUIRE(modifiesSManager->containsMap(6, "x"));
    REQUIRE(modifiesSManager->containsMap(7, "y"));
    REQUIRE(modifiesSManager->containsMap(8, "x"));
    REQUIRE(modifiesSManager->containsMap(8, "y"));
    REQUIRE(modifiesSManager->containsMap(9, "x"));
    REQUIRE(modifiesSManager->containsMap(11, "x"));
    REQUIRE(modifiesSManager->containsMap(13, "y"));
    REQUIRE(modifiesSManager->containsMap(14, "y"));
    REQUIRE(modifiesSManager->containsMap(15, "b"));
    REQUIRE(modifiesSManager->containsMap(15, "c"));
    REQUIRE(modifiesSManager->containsMap(16, "b"));
    REQUIRE(modifiesSManager->containsMap(17, "c"));
    REQUIRE(modifiesSManager->containsMap(18, "c"));
    REQUIRE(storedModifiesSMap.size() == modifiesS_map.size());
    REQUIRE(storedModifiesSMap == modifiesS_map);

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
    REQUIRE(modifiesSManager->containsReversedMap("b", 15));
    REQUIRE(modifiesSManager->containsReversedMap("b", 16));
    REQUIRE(modifiesSManager->containsReversedMap("c", 15));
    REQUIRE(modifiesSManager->containsReversedMap("c", 17));
    REQUIRE(modifiesSManager->containsReversedMap("c", 18));
    REQUIRE(storedReversedModifiesSMap.size() == reversed_modifiesS_map.size());
    REQUIRE(storedReversedModifiesSMap == reversed_modifiesS_map);

    // test ParentManager
    auto parentManager = readStorage->getParentManager();
    std::unordered_map<int, std::unordered_set<int>> parent_map = {{3, {4, 5, 6}}, {8, {9, 13}}, {9, {10, 11, 12}}};

    std::unordered_map<int, std::unordered_set<int>> reversed_parent_map = {{4, {3}}, {5, {3}}, {6, {3}},
                                                                            {9, {8}}, {13, {8}},  {10, {9}},
                                                                            {11, {9}}, {12, {9}}};

    auto storedParentMap = parentManager->getAllRelationshipEntries();
    auto storedReversedParentMap = parentManager->getAllReversedRelationshipEntries();

    REQUIRE(parentManager->containsMap(3, 4));
    REQUIRE(parentManager->containsMap(3, 5));
    REQUIRE(parentManager->containsMap(3, 6));
    REQUIRE(parentManager->containsMap(8, 9));
    REQUIRE(parentManager->containsMap(8, 13));
    REQUIRE(parentManager->containsMap(9, 10));
    REQUIRE(parentManager->containsMap(9, 11));
    REQUIRE(parentManager->containsMap(9, 12));
    REQUIRE(storedParentMap.size() == parent_map.size());
    REQUIRE(storedParentMap == parent_map);

    REQUIRE(parentManager->containsReversedMap(4, 3));
    REQUIRE(parentManager->containsReversedMap(5, 3));
    REQUIRE(parentManager->containsReversedMap(6, 3));
    REQUIRE(parentManager->containsReversedMap(9, 8));
    REQUIRE(parentManager->containsReversedMap(13, 8));
    REQUIRE(parentManager->containsReversedMap(10, 9));
    REQUIRE(parentManager->containsReversedMap(11, 9));
    REQUIRE(parentManager->containsReversedMap(12, 9));
    REQUIRE(storedReversedParentMap.size() == reversed_parent_map.size());
    REQUIRE(storedReversedParentMap == reversed_parent_map);

    // test ParentTManager
    auto parentTManager = readStorage->getParentTManager();
    std::unordered_map<int, std::unordered_set<int>> parentT_map = {{3, {4, 5, 6}}, {8, {9, 10, 11, 12, 13}},
                                                                    {9, {10, 11, 12}}};

    std::unordered_map<int, std::unordered_set<int>> reversed_parentT_map = {{4, {3}}, {5, {3}}, {6, {3}}, {9, {8}},
                                                                             {13, {8}},  {10, {8, 9}}, {11, {8, 9}},
                                                                             {12, {8, 9}}};

    auto storedParentTMap = parentTManager->getAllRelationshipEntries();
    auto storedReversedParentTMap = parentTManager->getAllReversedRelationshipEntries();

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
    REQUIRE(storedParentTMap.size() == parentT_map.size());
    REQUIRE(storedParentTMap == parentT_map);

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
    REQUIRE(storedReversedParentTMap.size() == reversed_parentT_map.size());
    REQUIRE(storedReversedParentTMap == reversed_parentT_map);

    // test UsesPManager
    auto usesPManager = readStorage->getUsesPManager();

    std::unordered_map<std::string, std::unordered_set<std::string>> usesP_map = {{"test1", {"a", "x", "y"}}};

    std::unordered_map<std::string, std::unordered_set<std::string>> reversed_usesP_map = {{"a", {"test1"}},
                                                                                           {"x", {"test1"}},
                                                                                           {"y", {"test1"}}};

    auto storedUsesPMap = usesPManager->getAllRelationshipEntries();
    auto storedReversedUsesPMap = usesPManager->getAllReversedRelationshipEntries();

    REQUIRE(usesPManager->containsMap("test1", "a"));
    REQUIRE(usesPManager->containsMap("test1", "x"));
    REQUIRE(usesPManager->containsMap("test1", "y"));
    REQUIRE(storedUsesPMap.size() == usesP_map.size());
    REQUIRE(storedUsesPMap == usesP_map);

    REQUIRE(usesPManager->containsReversedMap("a", "test1"));
    REQUIRE(usesPManager->containsReversedMap("x", "test1"));
    REQUIRE(usesPManager->containsReversedMap("y", "test1"));
    REQUIRE(storedReversedUsesPMap.size() == reversed_usesP_map.size());
    REQUIRE(storedReversedUsesPMap == reversed_usesP_map);

    // test UsesSManager
    auto usesSManager = readStorage->getUsesSManager();

    std::unordered_map<int, std::unordered_set<std::string>> usesS_map = {{3, {"a", "x"}}, {4, {"x"}}, {5, {"x"}},
                                                                          {8, {"x", "y"}}, {9, {"x"}}, {10, {"x"}},
                                                                          {12, {"x"}}, {13, {"y"}}, {14, {"x"}}};

    std::unordered_map<std::string, std::unordered_set<int>> reversed_usesS_map = {{"a", {3}},
                                                                                   {"x", {3, 4, 5, 8, 9, 10, 12, 14}},
                                                                                   {"y", {8, 13}}};

    auto storedUsesSMap = usesSManager->getAllRelationshipEntries();
    auto storedReversedUsesSMap = usesSManager->getAllReversedRelationshipEntries();

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
    REQUIRE(storedUsesSMap.size() == usesS_map.size());
    REQUIRE(storedUsesSMap == usesS_map);

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
    REQUIRE(storedReversedUsesSMap.size() == reversed_usesS_map.size());
    REQUIRE(storedReversedUsesSMap == reversed_usesS_map);

    // test callsPManager

    auto callsPManager = readStorage->getCallsPManager();

    std::unordered_map<std::string, std::unordered_set<std::string>> callsP_map = {{"test1", {"test2"}},
                                                                                   {"test2", {"test3"}}};

    std::unordered_map<std::string, std::unordered_set<std::string>> reversed_callsP_map = {{"test2", {"test1"}},
                                                                                            {"test3", {"test2"}}};

    auto storedCallsPMap = callsPManager->getAllRelationshipEntries();
    auto storedReversedCallsPMap = callsPManager->getAllReversedRelationshipEntries();

    REQUIRE(callsPManager->containsMap("test1", "test2"));
    REQUIRE(callsPManager->containsMap("test2", "test3"));
    REQUIRE(storedCallsPMap.size() == callsP_map.size());
    REQUIRE(storedCallsPMap == callsP_map);

    REQUIRE(callsPManager->containsReversedMap("test2", "test1"));
    REQUIRE(callsPManager->containsReversedMap("test3", "test2"));
    REQUIRE(storedReversedCallsPMap.size() == reversed_callsP_map.size());
    REQUIRE(storedReversedCallsPMap == reversed_callsP_map);

    // test CallsSManager
    auto callsSManager = readStorage->getCallsSManager();

    std::unordered_map<int, std::unordered_set<std::string>> callsS_map = {{15, {"test2"}}, {17, {"test3"}}};

    std::unordered_map<std::string, std::unordered_set<int>> reversed_callsS_map = {{"test2", {15}}, {"test3", {17}}};

    auto storedCallsSMap = callsSManager->getAllRelationshipEntries();
    auto storedReversedCallsSMap = callsSManager->getAllReversedRelationshipEntries();

    REQUIRE(callsSManager->containsMap(15, "test2"));
    REQUIRE(callsSManager->containsMap(17, "test3"));
    REQUIRE(storedCallsSMap.size() == callsS_map.size());
    REQUIRE(storedCallsSMap == callsS_map);

    REQUIRE(callsSManager->containsReversedMap("test2", 15));
    REQUIRE(callsSManager->containsReversedMap("test3", 17));
    REQUIRE(storedReversedCallsSMap.size() == reversed_callsS_map.size());
    REQUIRE(storedReversedCallsSMap == reversed_callsS_map);

    // test CallsTManager

    auto callsTManager = readStorage->getCallsTManager();

    std::unordered_map<std::string, std::unordered_set<std::string>> callsT_map = {{"test1", {"test2", "test3"}},
                                                                                   {"test2", {"test3"}}};

    std::unordered_map<std::string, std::unordered_set<std::string>> reversed_callsT_map = {{"test2", {"test1"}},
                                                                                            {"test3", {"test1",
                                                                                                       "test2"}}};

    auto storedCallsTMap = callsTManager->getAllRelationshipEntries();
    auto storedReversedCallsTMap = callsTManager->getAllReversedRelationshipEntries();

    REQUIRE(callsTManager->containsMap("test1", "test2"));
    REQUIRE(callsTManager->containsMap("test2", "test3"));
    REQUIRE(callsTManager->containsMap("test1", "test3"));
    REQUIRE(storedCallsTMap.size() == callsT_map.size());
    REQUIRE(storedCallsTMap == callsT_map);

    REQUIRE(callsTManager->containsReversedMap("test2", "test1"));
    REQUIRE(callsTManager->containsReversedMap("test3", "test2"));
    REQUIRE(callsTManager->containsReversedMap("test3", "test1"));
    REQUIRE(storedReversedCallsTMap.size() == reversed_callsT_map.size());
    REQUIRE(storedReversedCallsTMap == reversed_callsT_map);

    // test IfCondManager

    auto ifCondManager = readStorage->getIfCondManager();

    std::unordered_map<int, std::unordered_set<std::string>> ifCond_map = {{3, {"a"}}, {9, {"x"}}};

    std::unordered_map<std::string, std::unordered_set<int>> reversed_ifCond_map = {{"a", {3}}, {"x", {9}}};

    auto storedIfCondMap = ifCondManager->getAllRelationshipEntries();
    auto storedReversedIfCondMap = ifCondManager->getAllReversedRelationshipEntries();

    REQUIRE(ifCondManager->containsMap(3, "a"));
    REQUIRE(ifCondManager->containsMap(9, "x"));
    REQUIRE(storedIfCondMap.size() == ifCond_map.size());
    REQUIRE(storedIfCondMap == ifCond_map);

    REQUIRE(ifCondManager->containsReversedMap("a", 3));
    REQUIRE(ifCondManager->containsReversedMap("x", 9));
    REQUIRE(storedReversedIfCondMap.size() == reversed_ifCond_map.size());
    REQUIRE(storedReversedIfCondMap == reversed_ifCond_map);

    // test NextManager
    auto nextManager = readStorage->getNextManager();
    std::unordered_map<int, std::unordered_set<int>> next_map = {{1, {2}}, {2, {3}}, {3, {4, 6}}, {4, {5}}, {5, {7}},
                                                                 {6, {7}},  {7, {8}}, {8, {9, 14}},  {9, {10, 11}},
                                                                 {10, {13}}, {11, {12}}, {12, {13}}, {13, {8}},
                                                                 {14, {15}}, {16, {17}}};

    std::unordered_map<int, std::unordered_set<int>> reversed_next_map = {{2, {1}}, {3, {2}}, {4, {3}}, {6, {3}},
                                                                          {5, {4}}, {7, {5, 6}}, {8, {7, 13}}, {9, {8}},
                                                                          {14, {8}}, {10, {9}}, {11, {9}},
                                                                          {13, {10, 12}}, {12, {11}},
                                                                          {15, {14}}, {17, {16}}};

    auto storedNextMap = nextManager->getAllRelationshipEntries();
    auto storedReversedNextMap = nextManager->getAllReversedRelationshipEntries();

    REQUIRE(nextManager->containsMap(1, 2));
    REQUIRE(nextManager->containsMap(2, 3));
    REQUIRE(nextManager->containsMap(3, 4));
    REQUIRE(nextManager->containsMap(3, 6));
    REQUIRE(nextManager->containsMap(4, 5));
    REQUIRE(nextManager->containsMap(5, 7));
    REQUIRE(nextManager->containsMap(6, 7));
    REQUIRE(nextManager->containsMap(7, 8));
    REQUIRE(nextManager->containsMap(8, 9));
    REQUIRE(nextManager->containsMap(8, 14));
    REQUIRE(nextManager->containsMap(9, 10));
    REQUIRE(nextManager->containsMap(9, 11));
    REQUIRE(nextManager->containsMap(10, 13));
    REQUIRE(nextManager->containsMap(11, 12));
    REQUIRE(nextManager->containsMap(12, 13));
    REQUIRE(nextManager->containsMap(13, 8));
    REQUIRE(nextManager->containsMap(14, 15));
    REQUIRE(nextManager->containsMap(16, 17));
    REQUIRE(storedNextMap.size() == next_map.size());
    REQUIRE(storedNextMap == next_map);

    REQUIRE(nextManager->containsReversedMap(2, 1));
    REQUIRE(nextManager->containsReversedMap(3, 2));
    REQUIRE(nextManager->containsReversedMap(4, 3));
    REQUIRE(nextManager->containsReversedMap(6, 3));
    REQUIRE(nextManager->containsReversedMap(5, 4));
    REQUIRE(nextManager->containsReversedMap(7, 5));
    REQUIRE(nextManager->containsReversedMap(7, 6));
    REQUIRE(nextManager->containsReversedMap(8, 7));
    REQUIRE(nextManager->containsReversedMap(9, 8));
    REQUIRE(nextManager->containsReversedMap(14, 8));
    REQUIRE(nextManager->containsReversedMap(10, 9));
    REQUIRE(nextManager->containsReversedMap(11, 9));
    REQUIRE(nextManager->containsReversedMap(13, 10));
    REQUIRE(nextManager->containsReversedMap(12, 11));
    REQUIRE(nextManager->containsReversedMap(13, 12));
    REQUIRE(nextManager->containsReversedMap(8, 13));
    REQUIRE(nextManager->containsReversedMap(15, 14));
    REQUIRE(nextManager->containsReversedMap(17, 16));
    REQUIRE(storedReversedNextMap.size() == reversed_next_map.size());
    REQUIRE(storedReversedNextMap == reversed_next_map);

    // test WhileCondManager

    auto whileCondManager = readStorage->getWhileCondManager();

    std::unordered_map<int, std::unordered_set<std::string>> whileCond_map = {{8, {"y"}}};

    std::unordered_map<std::string, std::unordered_set<int>> reversed_whileCond_map = {{"y", {8}}};

    auto storedWhileCondMap = whileCondManager->getAllRelationshipEntries();
    auto storedReversedWhileCondMap = whileCondManager->getAllReversedRelationshipEntries();

    REQUIRE(whileCondManager->containsMap(8, "y"));
    REQUIRE(storedWhileCondMap == whileCond_map);
    REQUIRE(storedWhileCondMap == whileCond_map);

    REQUIRE(whileCondManager->containsReversedMap("y", 8));
    REQUIRE(storedReversedWhileCondMap.size() == reversed_whileCond_map.size());
    REQUIRE(storedReversedWhileCondMap.size() == reversed_whileCond_map.size());

    std::filesystem::remove(testFileName);
}
