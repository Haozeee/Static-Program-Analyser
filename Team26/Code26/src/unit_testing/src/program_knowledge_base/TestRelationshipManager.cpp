#include "catch.hpp"
#include "program_knowledge_base/relationship/RelationshipManager.h"
#include "program_knowledge_base/relationship/WriteOnlyRelationshipManager.h"
#include "program_knowledge_base/StorageUtil.h"
#include "program_knowledge_base/ReadOnlyStorage.h"
#include "program_knowledge_base/WriteOnlyStorage.h"

TEST_CASE("RelationshipManager insertRelationship int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 4));
    REQUIRE(relationshipManager.insertRelationship(3, 4));
}

TEST_CASE("RelationshipManager insertRelationship int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.insertRelationship(2, "y"));
}

TEST_CASE("RelationshipManager insertRelationship string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship("a", "x"));
    REQUIRE(relationshipManager.insertRelationship("a", "y"));
}

TEST_CASE("RelationshipManager isEmpty int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE(relationshipManager.isEmpty());
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE_FALSE(relationshipManager.isEmpty());
}

TEST_CASE("RelationshipManager isEmpty string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship("x", "y"));
    REQUIRE_FALSE(relationshipManager.isEmpty());
}

TEST_CASE("RelationshipManager isEmpty int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE(relationshipManager.isEmpty());
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE_FALSE(relationshipManager.isEmpty());
}

TEST_CASE("RelationshipManager contains int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE_FALSE(relationshipManager.contains(2, "x"));
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.contains(2, "x"));
}

TEST_CASE("RelationshipManager contains string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship("x", "y"));
    REQUIRE_FALSE(relationshipManager.isEmpty());
}

TEST_CASE("RelationshipManager contains int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE_FALSE(relationshipManager.contains(2, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.contains(2, 3));
}

TEST_CASE("RelationshipManager getAllRelationshipEntries int,int") {
    RelationshipManager<int, int> relationshipManager;
    std::unordered_map<int, std::unordered_set<int>> test_map = {{2, {3, 4}}};
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 4));
    REQUIRE(relationshipManager.getAllRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllRelationshipEntries int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    std::unordered_map<int, std::unordered_set<std::string>> test_map = {{2, {"x", "y"}}};
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
    REQUIRE(relationshipManager.insertRelationship(2, "y"));
    REQUIRE(relationshipManager.getAllRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllRelationshipEntries string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    std::unordered_map<std::string, std::unordered_set<std::string>> test_map = {{"a", {"x", "y"}}};
    REQUIRE(relationshipManager.insertRelationship("a", "x"));
    REQUIRE(relationshipManager.insertRelationship("a", "y"));
    REQUIRE(relationshipManager.getAllRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllReversedRelationshipEntries int,int") {
    RelationshipManager<int, int> relationshipManager;
    std::unordered_map<int, std::unordered_set<int>> test_map = {{3, {1,2}}};
    REQUIRE(relationshipManager.insertRelationship(1, 3));
    REQUIRE(relationshipManager.insertRelationship(2, 3));
    REQUIRE(relationshipManager.getAllReversedRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllReversedRelationshipEntries int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    std::unordered_map<std::string, std::unordered_set<int>> test_map = {{"a", {1}}, {"b",{1}}};
    REQUIRE(relationshipManager.insertRelationship(1, "a"));
    REQUIRE(relationshipManager.insertRelationship(1, "b"));
    REQUIRE(relationshipManager.getAllReversedRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager getAllReversedRelationshipEntries string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    std::unordered_map<std::string, std::unordered_set<std::string>> test_map = {{"a", {"x"}}, {"b",{"x"}}};
    REQUIRE(relationshipManager.insertRelationship("x", "a"));
    REQUIRE(relationshipManager.insertRelationship("x", "b"));
    REQUIRE(relationshipManager.getAllReversedRelationshipEntries() == test_map);
}

TEST_CASE("RelationshipManager _insert int,int,WriteOnlyRelationshipManager") {
    RelationshipManager<int, int> relationshipManager;

    REQUIRE(relationshipManager.insertRelationship(0, 1,
                                                   std::shared_ptr<WriteOnlyRelationshipManger<int, int>>()) == false);
    REQUIRE(relationshipManager.insertRelationship(1, 0,
                                                   std::shared_ptr<WriteOnlyRelationshipManger<int, int>>()) == false);

}

TEST_CASE("FollowsManager _insert int,int,WriteOnlyRelationshipManager") {
    std::shared_ptr<StorageUtil> storageUtil = std::make_shared<StorageUtil>();
    WriteOnlyStorage* writeOnlyStorage = new WriteOnlyStorage(storageUtil);
    REQUIRE(writeOnlyStorage->getFollowsManager()->insertRelationship(1, 2,
                                                                      writeOnlyStorage->getFollowsTManager()));
}
