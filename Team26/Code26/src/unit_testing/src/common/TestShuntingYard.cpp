#include "catch.hpp"
#include <string>
#include "common/parser/ShuntingYardParser.h"
#include "common/parser/ShuntNode.h"

std::string simpleTestExpression = "x+y";
std::string testExpression = "v+x*y+z*t";

TEST_CASE("Test Parse Correctly") {
    // Simple expression
    auto simpleExpressionTree = ShuntingYardParser::parse(simpleTestExpression);
    auto inOrder = ShuntNode::getInOrderTraversal(simpleExpressionTree);
    auto preOrder = ShuntNode::getPreOrderTraversal(simpleExpressionTree);
    REQUIRE(inOrder == "x+y");
    REQUIRE(preOrder == "+xy");

    // Complex expression
    auto expressionTree = ShuntingYardParser::parse(testExpression);
    inOrder = ShuntNode::getInOrderTraversal(expressionTree);
    preOrder = ShuntNode::getPreOrderTraversal(expressionTree);
    REQUIRE(inOrder == "v+x*y+z*t");
    REQUIRE(preOrder == "++v*xy*zt");
}

TEST_CASE("Test Is Match") {
    auto expressionTree = ShuntingYardParser::parse(testExpression);
    // Positive matches
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v")));
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("x*y")));
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v+x*y")));
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v+x*y+z*t")));

    // Negative matches
    REQUIRE_FALSE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v+x")));
    REQUIRE_FALSE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("y+z*t")));
    REQUIRE_FALSE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("x*y+z*t")));
}
