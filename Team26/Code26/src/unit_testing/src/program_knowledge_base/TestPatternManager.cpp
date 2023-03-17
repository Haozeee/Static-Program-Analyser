#include "catch.hpp"
#include "program_knowledge_base/pattern/PatternManager.h"
#include "common/parser/ShuntingYardParser.h"


// test isEmpty methods
TEST_CASE("PatternManager isEmptyLhsVector string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE(patternManager.isEmptyLhsVector());
    patternManager.insertPattern(1, "left", node);
    auto lhs = patternManager.getAllLhsPatternEntries();
    REQUIRE(lhs->size() == 1);
    REQUIRE_FALSE(patternManager.isEmptyLhsVector());
}

TEST_CASE("PatternManager isEmptyRhsVector string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE(patternManager.isEmptyRhsVector());
    patternManager.insertPattern(1, "left", node);
    auto rhs = patternManager.getAllLhsPatternEntries();
    REQUIRE(rhs->size() == 1);
    REQUIRE_FALSE(patternManager.isEmptyRhsVector());
}

TEST_CASE("PatternManager isEmptyIndexStmtMap string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE(patternManager.isEmptyIndexStmtMap());
    patternManager.insertPattern(1, "left", node);
    auto map = patternManager.getAllPatternEntries();
    REQUIRE(map.size() == 1);
    REQUIRE_FALSE(patternManager.isEmptyIndexStmtMap());
}

TEST_CASE("PatternManager isEmptyReversedIndexStmtMap string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE(patternManager.isEmptyReversedIndexStmtMap());
    patternManager.insertPattern(1, "left", node);
    auto reversedMap = patternManager.getAllReversedPatternEntries();
    REQUIRE(reversedMap.size() == 1);
    REQUIRE_FALSE(patternManager.isEmptyReversedIndexStmtMap());
}

// test contains methods
TEST_CASE("PatternManager containsLhsVector string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE_FALSE(patternManager.containsLhsVector("left"));
    patternManager.insertPattern(1, "left", node);
    auto lhs = patternManager.getAllLhsPatternEntries();
    REQUIRE(lhs->size() == 1);
    REQUIRE(patternManager.containsLhsVector("left"));
}

TEST_CASE("PatternManager containsRhsVector string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE_FALSE(patternManager.containsRhsVector(node));
    patternManager.insertPattern(1, "left", node);
    auto rhs = patternManager.getAllRhsPatternEntries();
    REQUIRE(rhs->size() == 1);
    REQUIRE(patternManager.containsRhsVector(node));
}

TEST_CASE("PatternManager containsIndexStmtMap string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE_FALSE(patternManager.containsIndexStmtMap(0, 1));
    patternManager.insertPattern(1, "left", node);
    auto map = patternManager.getAllPatternEntries();
    REQUIRE(map.size() == 1);
    REQUIRE(patternManager.containsIndexStmtMap(0, 1));
}

TEST_CASE("PatternManager containsReversedIndexStmtMap string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node = ShuntingYardParser::parse("x+y");
    REQUIRE_FALSE(patternManager.containsReversedIndexStmtMap(1, 0));
    patternManager.insertPattern(1, "left", node);
    auto reversedMap = patternManager.getAllReversedPatternEntries();
    REQUIRE(reversedMap.size() == 1);
    REQUIRE(patternManager.containsReversedIndexStmtMap(1, 0));
}

// testing getAll methods
TEST_CASE("PatternManager getAllLhsPatternEntries string,shuntNode") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node1 = ShuntingYardParser::parse("x+y");
    auto node2  = ShuntingYardParser::parse("a+b");
    auto set = patternManager.getAllLhsPatternEntries();
    REQUIRE(set->empty());
    std::vector<std::string> test_vector = {"left1", "left2"};
    patternManager.insertPattern(1, "left1", node1);
    patternManager.insertPattern(2, "left2", node2);
    set = patternManager.getAllLhsPatternEntries();
    REQUIRE(set->size() == 2);
    REQUIRE(*(patternManager.getAllLhsPatternEntries()) == test_vector);
}

TEST_CASE("PatternManager getAllRhsPatternEntries") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node1 = ShuntingYardParser::parse("x+y");
    auto node2  = ShuntingYardParser::parse("a+b");
    auto set = patternManager.getAllRhsPatternEntries();
    REQUIRE(set->empty());
    std::vector<std::shared_ptr<ShuntNode>> test_vector = {node1, node2};
    patternManager.insertPattern(1, "left1", node1);
    patternManager.insertPattern(2, "left2", node2);
    set = patternManager.getAllRhsPatternEntries();
    REQUIRE(set->size() == 2);
    REQUIRE(*(patternManager.getAllRhsPatternEntries()) == test_vector);
}


TEST_CASE("PatternManager getAllPatternEntries") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node1 = ShuntingYardParser::parse("x+y");
    auto node2  = ShuntingYardParser::parse("a+b");
    auto map = patternManager.getAllPatternEntries();
    REQUIRE(map.empty());
    std::unordered_map<int, int> test_map = {{0, 1}, {1, 2}};
    patternManager.insertPattern(1, "left1", node1);
    patternManager.insertPattern(2, "left2", node2);
    map = patternManager.getAllPatternEntries();
    REQUIRE(map.size() == 2);
    REQUIRE(patternManager.getAllPatternEntries() == test_map);
}

TEST_CASE("PatternManager getAllReversedPatternEntries") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node1 = ShuntingYardParser::parse("x+y");
    auto node2  = ShuntingYardParser::parse("a+b");
    auto map = patternManager.getAllReversedPatternEntries();
    REQUIRE(map.empty());
    std::unordered_map<int, int> test_map = {{1, 0}, {2, 1}};
    patternManager.insertPattern(1, "left1", node1);
    patternManager.insertPattern(2, "left2", node2);
    map = patternManager.getAllReversedPatternEntries();
    REQUIRE(map.size() == 2);
    REQUIRE(patternManager.getAllReversedPatternEntries() == test_map);
}

// testing insert method
TEST_CASE("PatternManager insertPattern") {
    PatternManager<std::string, std::shared_ptr<ShuntNode>> patternManager;
    auto node1 = ShuntingYardParser::parse("x+y");
    auto node2  = ShuntingYardParser::parse("a+b");
    auto node3  = ShuntingYardParser::parse("c");
    REQUIRE(patternManager.isEmptyLhsVector());
    REQUIRE(patternManager.isEmptyRhsVector());
    REQUIRE(patternManager.isEmptyIndexStmtMap());
    REQUIRE(patternManager.isEmptyReversedIndexStmtMap());
    patternManager.insertPattern(1, "left1", node1);
    patternManager.insertPattern(2, "left2", node2);
    patternManager.insertPattern(3, "left3", node3);
    REQUIRE_FALSE(patternManager.isEmptyLhsVector());
    REQUIRE_FALSE(patternManager.isEmptyRhsVector());
    REQUIRE_FALSE(patternManager.isEmptyIndexStmtMap());
    REQUIRE_FALSE(patternManager.isEmptyReversedIndexStmtMap());

    std::vector<std::string> lhs_vector = {"left1", "left2", "left3"};
    std::vector<std::shared_ptr<ShuntNode>> rhs_vector = {node1, node2, node3};
    std::unordered_map<int, int> test_map = {{0, 1}, {1, 2}, {2, 3}};
    std::unordered_map<int, int> reversed_test_map = {{1, 0}, {2, 1}, {3, 2}};
    auto lhs = patternManager.getAllLhsPatternEntries();
    auto rhs = patternManager.getAllRhsPatternEntries();
    auto map = patternManager.getAllPatternEntries();
    auto reversedMap = patternManager.getAllReversedPatternEntries();
    REQUIRE(lhs->size() == 3);
    REQUIRE(*lhs == lhs_vector);
    REQUIRE(rhs->size() == 3);
    REQUIRE(*rhs == rhs_vector);
    REQUIRE(map.size() == 3);
    REQUIRE(map == test_map);
    REQUIRE(reversedMap.size() == 3);
    REQUIRE(reversedMap == reversed_test_map);

    // invalid insert of duplicates
    REQUIRE_FALSE(patternManager.insertPattern(1, "left3", node3));
    REQUIRE_FALSE(patternManager.insertPattern(2, "left2", node2));
}
