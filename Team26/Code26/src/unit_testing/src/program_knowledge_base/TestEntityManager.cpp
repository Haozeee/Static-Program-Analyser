#include "catch.hpp"
#include "program_knowledge_base/entity/EntityManager.h"

TEST_CASE("EntityManager insertEntity int") {
    EntityManager<int> entityManager;

    // reject repeated entry
    REQUIRE(entityManager.insertEntity(3));
    REQUIRE_FALSE(entityManager.insertEntity(3));

    // insert new
    REQUIRE(entityManager.insertEntity(4));
}

TEST_CASE("EntityManager insertEntity string") {
    EntityManager<std::string> entityManager;

    // reject repeated entry
    REQUIRE(entityManager.insertEntity("x"));
    REQUIRE_FALSE(entityManager.insertEntity("x"));

    // insert new
    REQUIRE(entityManager.insertEntity("flag"));
}

TEST_CASE("EntityManager isEmpty int") {
    EntityManager<int> entityManager;
    REQUIRE(entityManager.isEmpty());
    REQUIRE(entityManager.insertEntity(3));
    REQUIRE_FALSE(entityManager.isEmpty());
}

TEST_CASE("EntityManager isEmpty string") {
    EntityManager<std::string> entityManager;
    REQUIRE(entityManager.isEmpty());
    REQUIRE(entityManager.insertEntity("x"));
    REQUIRE_FALSE(entityManager.isEmpty());
}

TEST_CASE("EntityManager contains int") {
    EntityManager<int> entityManager;
    REQUIRE_FALSE(entityManager.contains(3));
    REQUIRE(entityManager.insertEntity(3));
    REQUIRE(entityManager.contains(3));
}

TEST_CASE("EntityManager contains string") {
    EntityManager<std::string> entityManager;
    REQUIRE_FALSE(entityManager.contains("x"));
    REQUIRE(entityManager.insertEntity("x"));
    REQUIRE(entityManager.contains("x"));
}

TEST_CASE("EntityManager getAllEntitiesEntries int") {
    EntityManager<int> entityManager;
    auto set = entityManager.getAllEntitiesEntries();
    REQUIRE(set.size() == 0);
    std::unordered_set<int> stmtNo_set = {3, 11};
    std::unordered_set<int> empty_set = {};
    REQUIRE(entityManager.insertEntity(3));
    REQUIRE(entityManager.insertEntity(11));
    set = entityManager.getAllEntitiesEntries();
    REQUIRE(set.size() == 2);
    REQUIRE(entityManager.getAllEntitiesEntries() == stmtNo_set);
    REQUIRE_FALSE(entityManager.getAllEntitiesEntries() == empty_set);
}

TEST_CASE("EntityManager getAllEntitiesEntries string") {
    EntityManager<std::string> entityManager;
    auto set = entityManager.getAllEntitiesEntries();
    REQUIRE(set.size() == 0);
    std::unordered_set<std::string> varName_set = {"x", "radius"};
    std::unordered_set<std::string> empty_set = {};
    REQUIRE(entityManager.insertEntity("x"));
    REQUIRE(entityManager.insertEntity("radius"));
    set = entityManager.getAllEntitiesEntries();
    REQUIRE(set.size() == 2);
    REQUIRE(entityManager.getAllEntitiesEntries() == varName_set);
    REQUIRE_FALSE(entityManager.getAllEntitiesEntries() == empty_set);
}