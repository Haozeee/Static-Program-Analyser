#include "catch.hpp"
#include "program_knowledge_base/pattern/PatternManager.h"

// test isEmpty methods
TEST_CASE("PatternManager isEmptyLhsVector") {
    PatternManager patternManager;
    REQUIRE(patternManager.isEmptyLhsVector());
    patternManager.insertPattern(1, "left", "right");
    REQUIRE_FALSE(patternManager.isEmptyLhsVector());
}

TEST_CASE("PatternManager isEmptyRhsVector") {
    PatternManager patternManager;
    REQUIRE(patternManager.isEmptyRhsVector());
    patternManager.insertPattern(1, "left", "right");
    REQUIRE_FALSE(patternManager.isEmptyRhsVector());
}

TEST_CASE("PatternManager isEmptyIndexStmtMap") {
    PatternManager patternManager;
    REQUIRE(patternManager.isEmptyIndexStmtMap());
    patternManager.insertPattern(1, "left", "right");
    REQUIRE_FALSE(patternManager.isEmptyIndexStmtMap());
}

TEST_CASE("PatternManager isEmptyReversedIndexStmtMap") {
    PatternManager patternManager;
    REQUIRE(patternManager.isEmptyReversedIndexStmtMap());
    patternManager.insertPattern(1, "left", "right");
    REQUIRE_FALSE(patternManager.isEmptyReversedIndexStmtMap());
}

// test contains methods
TEST_CASE("PatternManager containsLhsVector") {
    PatternManager patternManager;
    REQUIRE_FALSE(patternManager.containsLhsVector("left"));
    patternManager.insertPattern(1, "left", "right");
    REQUIRE(patternManager.containsLhsVector("left"));
}

TEST_CASE("PatternManager containsRhsVector") {
    PatternManager patternManager;
    REQUIRE_FALSE(patternManager.containsRhsVector("right"));
    patternManager.insertPattern(1, "left", "right");
    REQUIRE(patternManager.containsRhsVector("right"));
}

TEST_CASE("PatternManager containsIndexStmtMap") {
    PatternManager patternManager;
    REQUIRE_FALSE(patternManager.containsIndexStmtMap(0, 1));
    patternManager.insertPattern(1, "left", "right");
    REQUIRE(patternManager.containsIndexStmtMap(0, 1));
}

TEST_CASE("PatternManager containsReversedIndexStmtMap") {
    PatternManager patternManager;
    REQUIRE_FALSE(patternManager.containsReversedIndexStmtMap(1, 0));
    patternManager.insertPattern(1, "left", "right");
    REQUIRE(patternManager.containsReversedIndexStmtMap(1, 0));
}

// testing getAll methods
TEST_CASE("PatternManager getAllLhsPatternEntries") {
    PatternManager patternManager;
    std::vector<std::string> test_vector = {"left1", "left2"};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    REQUIRE(patternManager.getAllLhsPatternEntries() == test_vector);
}

TEST_CASE("PatternManager getAllRhsPatternEntries") {
    PatternManager patternManager;
    std::vector<std::string> test_vector = {"right1", "right2"};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    REQUIRE(patternManager.getAllRhsPatternEntries() == test_vector);
}

TEST_CASE("PatternManager getAllPatternEntries") {
    PatternManager patternManager;
    std::unordered_map<int, int> test_map = {{0, 1}, {1, 2}};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    REQUIRE(patternManager.getAllPatternEntries() == test_map);
}

TEST_CASE("PatternManager getAllReversedPatternEntries") {
    PatternManager patternManager;
    std::unordered_map<int, int> test_map = {{1, 0}, {2, 1}};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    REQUIRE(patternManager.getAllReversedPatternEntries() == test_map);
}

// testing insert method
TEST_CASE("PatternManager insertPattern") {
    PatternManager patternManager;
    REQUIRE(patternManager.isEmptyIndexStmtMap());
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    REQUIRE_FALSE(patternManager.isEmptyIndexStmtMap());
}
