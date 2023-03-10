#include "catch.hpp"
#include "program_knowledge_base/pattern/PatternManager.h"

using StringList = std::vector<std::string>;
std::string simpleTestExpression = "x+y";
std::string testExpression = "v+x*y+z*t";

// test isEmpty methods
TEST_CASE("PatternManager isEmptyLhsVector") {
    PatternManager patternManager;
    auto node = std::make_shared<ShuntNode>(simpleTestExpression);
    REQUIRE(patternManager.isEmptyLhsVector());
    patternManager.insertPattern(1, "left", node);
    REQUIRE_FALSE(patternManager.isEmptyLhsVector());
}

/*
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
    auto set = patternManager.getAllLhsPatternEntries();
    REQUIRE(set.size() == 0);
    std::vector<std::string> test_vector = {"left1", "left2"};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    set = patternManager.getAllLhsPatternEntries();
    REQUIRE(set.size() == 2);
    REQUIRE(patternManager.getAllLhsPatternEntries() == test_vector);
}

TEST_CASE("PatternManager getAllRhsPatternEntries") {
    PatternManager patternManager;
    auto set = patternManager.getAllRhsPatternEntries();
    REQUIRE(set.size() == 0);
    std::vector<std::string> test_vector = {"right1", "right2"};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    set = patternManager.getAllRhsPatternEntries();
    REQUIRE(set.size() == 2);
    REQUIRE(patternManager.getAllRhsPatternEntries() == test_vector);
}

TEST_CASE("PatternManager getAllPatternEntries") {
    PatternManager patternManager;
    auto map = patternManager.getAllPatternEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<int, int> test_map = {{0, 1}, {1, 2}};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    map = patternManager.getAllPatternEntries();
    REQUIRE(map.size() == 2);
    REQUIRE(patternManager.getAllPatternEntries()[0] == 1);
    REQUIRE(patternManager.getAllPatternEntries() == test_map);
}

TEST_CASE("PatternManager getAllReversedPatternEntries") {
    PatternManager patternManager;
    auto map = patternManager.getAllReversedPatternEntries();
    REQUIRE(map.size() == 0);
    std::unordered_map<int, int> test_map = {{1, 0}, {2, 1}};
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    map = patternManager.getAllReversedPatternEntries();
    REQUIRE(map.size() == 2);
    REQUIRE(patternManager.getAllReversedPatternEntries()[2] == 1);
    REQUIRE(patternManager.getAllReversedPatternEntries() == test_map);
}

// testing insert method
TEST_CASE("PatternManager insertPattern") {
    PatternManager patternManager;
    REQUIRE(patternManager.isEmptyLhsVector());
    REQUIRE(patternManager.isEmptyRhsVector());
    REQUIRE(patternManager.isEmptyIndexStmtMap());
    REQUIRE(patternManager.isEmptyReversedIndexStmtMap());
    patternManager.insertPattern(1, "left1", "right1");
    patternManager.insertPattern(2, "left2", "right2");
    patternManager.insertPattern(3, "left3", "right3");
    auto lhs = patternManager.getAllLhsPatternEntries();
    auto rhs = patternManager.getAllRhsPatternEntries();
    auto map = patternManager.getAllPatternEntries();
    auto reversedMap = patternManager.getAllReversedPatternEntries();
    REQUIRE(lhs.size() == 3);
    REQUIRE(rhs.size() == 3);
    REQUIRE(map.size() == 3);
    REQUIRE(reversedMap.size() == 3);
    REQUIRE_FALSE(patternManager.isEmptyLhsVector());
    REQUIRE_FALSE(patternManager.isEmptyRhsVector());
    REQUIRE_FALSE(patternManager.isEmptyIndexStmtMap());
    REQUIRE_FALSE(patternManager.isEmptyReversedIndexStmtMap());

    // invalid insert
    REQUIRE_FALSE(patternManager.insertPattern(1, "left3", "right3"));
}
*/