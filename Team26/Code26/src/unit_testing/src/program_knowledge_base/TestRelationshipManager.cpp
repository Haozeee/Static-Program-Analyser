#include "catch.hpp"
#include "program_knowledge_base/relationship/RelationshipManager.h"
#include "program_knowledge_base/relationship/IWriteRelationshipManager.h"
#include "program_knowledge_base/StorageUtil.h"
#include "program_knowledge_base/StorageManager.h"

// testing isEmpty
TEST_CASE("RelationshipManager isEmptyMap int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE(relationshipManager.isEmptyMap());
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE_FALSE(relationshipManager.isEmptyMap());
}

TEST_CASE("RelationshipManager isEmptyMap string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.isEmptyMap());
    REQUIRE(relationshipManager.insertRelationship("x", "y"));
    REQUIRE_FALSE(relationshipManager.isEmptyMap());
}

TEST_CASE("RelationshipManager isEmptyMap int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE(relationshipManager.isEmptyMap());
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE_FALSE(relationshipManager.isEmptyMap());
}

TEST_CASE("RelationshipManager isEmptyReversedMap int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE(relationshipManager.isEmptyReversedMap());
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.isEmptyReversedMap());
    relationshipManager.setReverse();
    REQUIRE_FALSE(relationshipManager.isEmptyReversedMap());
}

TEST_CASE("RelationshipManager isEmptyReversedMap string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.isEmptyReversedMap());
    REQUIRE(relationshipManager.insertRelationship("x", "y"));
    REQUIRE(relationshipManager.isEmptyReversedMap());
    relationshipManager.setReverse();
    REQUIRE_FALSE(relationshipManager.isEmptyReversedMap());
}

TEST_CASE("RelationshipManager isEmptyReversedMap int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE(relationshipManager.isEmptyReversedMap());
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.isEmptyReversedMap());
    relationshipManager.setReverse();
    REQUIRE_FALSE(relationshipManager.isEmptyReversedMap());
}

// testing contains method
TEST_CASE("RelationshipManager containsMap int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE_FALSE(relationshipManager.containsMap(2, "x"));
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.containsMap(2, "x"));
}

TEST_CASE("RelationshipManager containsMap string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE_FALSE(relationshipManager.containsMap("x", "y"));
    REQUIRE(relationshipManager.insertRelationship("x", "y"));
    REQUIRE_FALSE(relationshipManager.isEmptyMap());
}

TEST_CASE("RelationshipManager containsMap int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE_FALSE(relationshipManager.containsMap(2, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.containsMap(2, 3));
}

TEST_CASE("RelationshipManager containsReversedMap int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE_FALSE(relationshipManager.containsReversedMap("x", 2));
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    relationshipManager.setReverse();
    REQUIRE(relationshipManager.containsReversedMap("x", 2));
}

TEST_CASE("RelationshipManager containsReversedMap string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE_FALSE(relationshipManager.containsReversedMap("y", "x"));
    REQUIRE(relationshipManager.insertRelationship("x", "y"));
    relationshipManager.setReverse();
    REQUIRE(relationshipManager.containsReversedMap("y", "x"));
}

TEST_CASE("RelationshipManager containsReversedMap int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE_FALSE(relationshipManager.containsMap(3, 2));
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    relationshipManager.setReverse();
    REQUIRE(relationshipManager.containsReversedMap(3, 2));
}

// testing getAll methods
TEST_CASE("RelationshipManager getAllRelationshipEntries int,int") {
    RelationshipManager<int, int> relationshipManager;
    auto map = relationshipManager.getAllRelationshipEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<int, std::unordered_set<int>> test_map = {{2, {3, 4}}};
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 4));
    map = relationshipManager.getAllRelationshipEntries();
    auto set = relationshipManager.getAllRelationshipEntries()[2];
    REQUIRE(map.size() == 1);
    REQUIRE(set.size() == 2);
    REQUIRE(relationshipManager.getAllRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllRelationshipEntries int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    auto map = relationshipManager.getAllRelationshipEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<int, std::unordered_set<std::string>> test_map = {{2, {"x", "y"}}};
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.insertRelationship(2, "y"));
    map = relationshipManager.getAllRelationshipEntries();
    auto set = relationshipManager.getAllRelationshipEntries()[2];
    REQUIRE(map.size() == 1);
    REQUIRE(set.size() == 2);
    REQUIRE(relationshipManager.getAllRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllRelationshipEntries string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    auto map = relationshipManager.getAllRelationshipEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<std::string, std::unordered_set<std::string>> test_map = {{"a", {"x", "y"}}};
    REQUIRE(relationshipManager.insertRelationship("a", "x"));
    REQUIRE(relationshipManager.insertRelationship("a", "y"));
    map = relationshipManager.getAllRelationshipEntries();
    auto set = relationshipManager.getAllRelationshipEntries()["a"];
    REQUIRE(map.size() == 1);
    REQUIRE(set.size() == 2);
    REQUIRE(relationshipManager.getAllRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllReversedRelationshipEntries int,int") {
    RelationshipManager<int, int> relationshipManager;
    auto map = relationshipManager.getAllReversedRelationshipEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<int, std::unordered_set<int>> test_map = {{3, {1,2}}};
    REQUIRE(relationshipManager.insertRelationship(1, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    relationshipManager.setReverse();
    map = relationshipManager.getAllReversedRelationshipEntries();
    auto set = relationshipManager.getAllReversedRelationshipEntries()[3];
    REQUIRE(map.size() == 1);
    REQUIRE(set.size() == 2);
    REQUIRE(relationshipManager.getAllReversedRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllReversedRelationshipEntries int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    auto map = relationshipManager.getAllReversedRelationshipEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<std::string, std::unordered_set<int>> test_map = {{"a", {1}}, {"b",{1}}};
    REQUIRE(relationshipManager.insertRelationship(1, "a"));
    REQUIRE(relationshipManager.insertRelationship(1, "b"));
    relationshipManager.setReverse();
    map = relationshipManager.getAllReversedRelationshipEntries();
    auto set = relationshipManager.getAllReversedRelationshipEntries()["b"];
    REQUIRE(map.size() == 2);
    REQUIRE(set.size() == 1);
    REQUIRE(relationshipManager.getAllReversedRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllReversedRelationshipEntries string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    auto map = relationshipManager.getAllReversedRelationshipEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<std::string, std::unordered_set<std::string>> test_map = {{"a", {"x"}}, {"b",{"x"}}};
    REQUIRE(relationshipManager.insertRelationship("x", "a"));
    REQUIRE(relationshipManager.insertRelationship("x", "b"));
    relationshipManager.setReverse();
    map = relationshipManager.getAllReversedRelationshipEntries();
    auto set = relationshipManager.getAllReversedRelationshipEntries()["b"];
    REQUIRE(map.size() == 2);
    REQUIRE(set.size() == 1);
    REQUIRE(relationshipManager.getAllReversedRelationshipEntries() == test_map);
}

// testing insertRelationship
TEST_CASE("RelationshipManager insertRelationship int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 4));
    REQUIRE(relationshipManager.insertRelationship(3, 4));
    auto map = relationshipManager.getAllRelationshipEntries();
    REQUIRE(map.size() == 2);
    auto set = relationshipManager.getAllRelationshipEntries()[2];
    REQUIRE(set.size() == 2);
    REQUIRE(set.find(3) != set.end());

    // invalid insertion
    REQUIRE_FALSE(relationshipManager.insertRelationship(3, 4));
    REQUIRE(map.size() == 2);
    REQUIRE(relationshipManager.isEmptyReversedMap());
}

TEST_CASE("RelationshipManager insertRelationship int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.insertRelationship(2, "y"));
    REQUIRE(relationshipManager.insertRelationship(3, "x"));
    auto map = relationshipManager.getAllRelationshipEntries();
    REQUIRE(map.size() == 2);
    auto set = relationshipManager.getAllRelationshipEntries()[2];
    REQUIRE(set.size() == 2);
    REQUIRE(set.find("x") != set.end());

    // invalid insertion
    REQUIRE_FALSE(relationshipManager.insertRelationship(3, "x"));
    REQUIRE(map.size() == 2);
    REQUIRE(relationshipManager.isEmptyReversedMap());

}

TEST_CASE("RelationshipManager insertRelationship string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship("a", "x"));
    REQUIRE(relationshipManager.insertRelationship("a", "y"));
    REQUIRE(relationshipManager.insertRelationship("b", "x"));
    auto map = relationshipManager.getAllRelationshipEntries();
    REQUIRE(map.size() == 2);
    auto set = relationshipManager.getAllRelationshipEntries()["a"];
    REQUIRE(set.size() == 2);
    REQUIRE(set.find("x") != set.end());

    // invalid insertion
    REQUIRE_FALSE(relationshipManager.insertRelationship("b", "x"));
    REQUIRE(map.size() == 2);
    REQUIRE(relationshipManager.isEmptyReversedMap());

}

// testing setReverse
TEST_CASE("RelationshipManager setReverse int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE(relationshipManager.isEmptyMap());
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 4));
    REQUIRE(relationshipManager.insertRelationship(3, 4));
    relationshipManager.setReverse();
    auto reversedMap = relationshipManager.getAllReversedRelationshipEntries();
    REQUIRE(reversedMap.size() == 2);
    auto reversedSet = relationshipManager.getAllReversedRelationshipEntries()[4];
    REQUIRE(reversedSet.size() == 2);
    REQUIRE(reversedSet.find(2) != reversedSet.end());
    REQUIRE_FALSE(relationshipManager.isEmptyMap());
}

TEST_CASE("RelationshipManager setReverse string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship("a", "x"));
    REQUIRE(relationshipManager.insertRelationship("a", "y"));
    REQUIRE(relationshipManager.insertRelationship("b", "x"));
    relationshipManager.setReverse();
    auto reversedMap = relationshipManager.getAllReversedRelationshipEntries();
    REQUIRE(reversedMap.size() == 2);
    auto reversedSet = relationshipManager.getAllReversedRelationshipEntries()["x"];
    REQUIRE(reversedSet.size() == 2);
    REQUIRE(reversedSet.find("b") != reversedSet.end());
    REQUIRE_FALSE(relationshipManager.isEmptyMap());
}

TEST_CASE("RelationshipManager setReverse int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.insertRelationship(2, "y"));
    REQUIRE(relationshipManager.insertRelationship(3, "x"));
    relationshipManager.setReverse();
    auto reversedMap = relationshipManager.getAllReversedRelationshipEntries();
    REQUIRE(reversedMap.size() == 2);
    auto reversedSet = relationshipManager.getAllReversedRelationshipEntries()["x"];
    REQUIRE(reversedSet.size() == 2);
    REQUIRE(reversedSet.find(2) != reversedSet.end());
    REQUIRE_FALSE(relationshipManager.isEmptyMap());
}

// testing overloaded insertRelationship
TEST_CASE("RelationshipManager _insert int,int,WriteOnlyRelationshipManager") {
    RelationshipManager<int, int> relationshipManager;

    REQUIRE(relationshipManager.insertRelationship(0, 1,
                                                   std::shared_ptr<IWriteRelationshipManager<int, int>>()) == false);
    REQUIRE(relationshipManager.insertRelationship(1, 0,
                                                   std::shared_ptr<IWriteRelationshipManager<int, int>>()) == false);

}

TEST_CASE("FollowsManager _insert int,int,WriteOnlyRelationshipManager") {
    std::shared_ptr<StorageManager> storageManager = std::make_shared<StorageManager>();
    auto writeStorage = storageManager->getWriteStorage();
    auto readStorage = storageManager->getReadStorage();
    auto followsManagerWrite = writeStorage->getFollowsManager();
    auto followsTManagerWrite = writeStorage->getFollowsTManager();
    REQUIRE(followsManagerWrite->insertRelationship(1, 2, followsTManagerWrite));
    REQUIRE(followsManagerWrite->insertRelationship(2, 3, followsTManagerWrite));
    REQUIRE(followsManagerWrite->insertRelationship(3, 4, followsTManagerWrite));
    followsManagerWrite->setReverse();
    auto followsManagerRead = readStorage->getFollowsManager();
    auto followsTManagerRead = readStorage->getFollowsTManager();

    auto map = followsManagerRead->getAllRelationshipEntries();
    auto reversedMap = followsManagerRead->getAllReversedRelationshipEntries();
    REQUIRE(map.size() == 3);
    REQUIRE(reversedMap.size() == 3);
    auto set = followsManagerRead->getAllRelationshipEntries()[1];
    auto reversedSet = followsManagerRead->getAllReversedRelationshipEntries()[3];
    REQUIRE(set.size() == 1);
    REQUIRE(reversedSet.size() == 1);
    REQUIRE(set.find(2) != set.end());
    REQUIRE(reversedSet.find(2) != reversedSet.end());

    // TODO: (ZH) Remove transitive
//    map = followsTManagerRead->getAllRelationshipEntries();
//    reversedMap = followsTManagerRead->getAllReversedRelationshipEntries();
//    REQUIRE(map.size() == 3);
//    REQUIRE(reversedMap.size() == 3);
//    set = followsTManagerRead->getAllRelationshipEntries()[1];
//    reversedSet = followsTManagerRead->getAllReversedRelationshipEntries()[4];
//    REQUIRE(set.size() == 3);
//    REQUIRE(reversedSet.size() == 3);
//    REQUIRE(set.find(2) != set.end());
//    REQUIRE(reversedSet.find(2) != reversedSet.end());
//
//    // invalid insertion
//    REQUIRE_FALSE(followsManagerWrite->insertRelationship(1, 2,followsTManagerWrite));
}

TEST_CASE("ParentManager _insert int,int,WriteOnlyRelationshipManager") {
    std::shared_ptr<StorageManager> storageManager = std::make_shared<StorageManager>();
    auto writeStorage = storageManager->getWriteStorage();
    auto readStorage = storageManager->getReadStorage();
    auto parentManagerWrite = writeStorage->getParentManager();
    auto parentTManagerWrite = writeStorage->getParentTManager();
    REQUIRE(parentManagerWrite->insertRelationship(4, 5, parentTManagerWrite));
    REQUIRE(parentManagerWrite->insertRelationship(4, 6, parentTManagerWrite));
    REQUIRE(parentManagerWrite->insertRelationship(3, 4, parentTManagerWrite));
    REQUIRE(parentManagerWrite->insertRelationship(1, 3, parentTManagerWrite));
    REQUIRE(parentManagerWrite->insertRelationship(1, 2,parentTManagerWrite));
    parentManagerWrite->setReverse();
    auto parentManagerRead = readStorage->getParentManager();
    auto parentTManagerRead = readStorage->getParentTManager();

    auto map = parentManagerRead->getAllRelationshipEntries();
    auto reversedMap = parentManagerRead->getAllReversedRelationshipEntries();
    REQUIRE(map.size() == 3);
    REQUIRE(reversedMap.size() == 5);
    auto set = parentManagerRead->getAllRelationshipEntries()[1];
    auto reversedSet = parentManagerRead->getAllReversedRelationshipEntries()[3];
    REQUIRE(set.size() == 2);
    REQUIRE(reversedSet.size() == 1);
    REQUIRE(set.find(2) != set.end());
    REQUIRE(reversedSet.find(1) != reversedSet.end());

    // TODO: (ZH) Remove transitive
//    map = parentTManagerRead->getAllRelationshipEntries();
//    reversedMap = parentTManagerRead->getAllReversedRelationshipEntries();
//    REQUIRE(map.size() == 3);
//    REQUIRE(reversedMap.size() == 5);
//    set = parentTManagerRead->getAllRelationshipEntries()[1];
//    reversedSet = parentTManagerRead->getAllReversedRelationshipEntries()[4];
//    REQUIRE(set.size() == 5);
//    REQUIRE(reversedSet.size() == 2);
//    REQUIRE(set.find(2) != set.end());
//    REQUIRE(reversedSet.find(3) != reversedSet.end());
//
//    // invalid insertion
//    REQUIRE_FALSE(parentManagerWrite->insertRelationship(1, 2,parentTManagerWrite));
}