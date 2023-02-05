#include "catch.hpp"
#include "program_knowledge_base/relationship/RelationshipManager.h"

TEST_CASE("RelationshipManager insertRelationship int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship(2, "x"));
}

TEST_CASE("RelationshipManager insertRelationship string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship("x", "y"));
}

TEST_CASE("RelationshipManager insertRelationship int,int") {
    RelationshipManager<int, int> relationshipManager;
    REQUIRE(relationshipManager.insertRelationship(2, 2));
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

TEST_CASE("RelationshipManager getAllRelationshipEntries int,string") {
    RelationshipManager<int, std::string> relationshipManager;
    std::unordered_map<int, std::string> relationships_map = {{1, "x"}, {2, "y"}};
    relationshipManager.insertRelationship(1, "x");
    relationshipManager.insertRelationship(2, "y");
    REQUIRE(relationshipManager.getAllRelationshipEntries() == relationships_map);
}

TEST_CASE("RelationshipManager getAllRelationshipEntries string,string") {
    RelationshipManager<std::string, std::string> relationshipManager;
    std::unordered_map<std::string, std::string> relationships_map = {{"Area", "x"}, {"Perimeter", "y"}};
    relationshipManager.insertRelationship("Area", "x");
    relationshipManager.insertRelationship("Perimeter", "y");
    REQUIRE(relationshipManager.getAllRelationshipEntries() == relationships_map);
}

TEST_CASE("RelationshipManager getAllRelationshipEntries int,int") {
    RelationshipManager<int, int> relationshipManager;
    std::unordered_map<int, int> relationships_map = {{1, 2}, {2, 3}};
    relationshipManager.insertRelationship(1, 2);
    relationshipManager.insertRelationship(2, 3);
    REQUIRE(relationshipManager.getAllRelationshipEntries() == relationships_map);
}
