#include "catch.hpp"
#include <string>
#include <vector>
#include "common/parser/ShuntingYardParser.h"
#include "common/parser/ShuntNode.h"

using StringList = std::vector<std::string>;
std::string simpleTestExpression = "x+y";
std::string testExpression = "v+x*y+z*t";
std::string invalidTestExpression = "v+x*y(+z*t";
std::string invalidConsecutiveFactorExpression = "a b + c";
std::string invalidVariableExpression = "g z t";
std::string invalidOperatorTestExpression = "v+^x*y(+z*t";

//  expr: expr '+' term | expr '-' term | term
//  term: term '*' factor | term '/' factor | term '%' factor | factor
//  factor: var_name | const_value | '(' expr ')'

std::vector<std::string> validTestExpressions {
    "1",
    "a",
    "( a    )",
    "  ( 1 )",
    " ( (1))",
    "(      ( a ) )",
    "4 + 3 * 4",
    "a - 4 * a",
    "4 * 4 - 3",
    "1 / 5"
};

std::vector<std::string> invalidTestExpressions {
    "3 + * 4",
    "5 - (6 * 7))",
    "2 ^ 3 ^ 4",
    "2 + (3 * )",
    "(())",
    "(7 + 2) /",
    "(+)",
    "10 % 3.5",
    "(7 - 4)(5 + 2)",
    "2 ++ 3",
    "(5 + 2)(4 - 3) 2",
    "3 + * a",
    "c - (b * 7))",
    "2 ^ d ^ 4",
    "2 + (e * )",
    "(7 + d) /",
    "(+)",
    "f % 3.5",
    "(7 - q)(5 + 2)",
    "2 ++ q",
    "(5 + 2)(4 - q) 2",
};

TEST_CASE("Valid Expression") {
    for (const auto & expression : validTestExpressions) {
        REQUIRE_NOTHROW(ShuntingYardParser::parse(expression));
    }
}

TEST_CASE("Test Parse Correctly") {
    // Simple expression
    auto simpleExpressionTree = ShuntingYardParser::parse(simpleTestExpression);
    auto inOrder = ShuntNode::getInOrderTraversal(simpleExpressionTree);
    auto preOrder = ShuntNode::getPreOrderTraversal(simpleExpressionTree);
    StringList expectedInOrder = {"x", "+", "y"};
    StringList expectedPreOrder = {"+", "x", "y"};
    REQUIRE(inOrder == expectedInOrder);
    REQUIRE(preOrder == expectedPreOrder);

    // Complex expression
    auto expressionTree = ShuntingYardParser::parse(testExpression);
    inOrder = ShuntNode::getInOrderTraversal(expressionTree);
    preOrder = ShuntNode::getPreOrderTraversal(expressionTree);
    expectedInOrder = {"v", "+", "x", "*", "y", "+", "z", "*", "t"};
    expectedPreOrder = {"+", "+", "v", "*", "x", "y", "*", "z", "t"};
    REQUIRE(inOrder == expectedInOrder);
    REQUIRE(preOrder == expectedPreOrder);
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

TEST_CASE("Test Invalid Expression") {
    REQUIRE_THROWS(ShuntingYardParser::parse(invalidTestExpression));
    REQUIRE_THROWS(ShuntingYardParser::parse(invalidOperatorTestExpression));
    REQUIRE_THROWS(ShuntingYardParser::parse(invalidConsecutiveFactorExpression));
    REQUIRE_THROWS(ShuntingYardParser::parse(invalidVariableExpression));

    for (const auto & expression : invalidTestExpressions) {
        REQUIRE_THROWS(ShuntingYardParser::parse(expression));
    }
}

TEST_CASE("Test String Produces Same Tree") {
    std::string stringA = "a+b";
    std::string stringB = "(a+b)";
    std::string stringC = "a + b";
    // The 2 strings are not equals but should produce the same tree
    REQUIRE(*(ShuntingYardParser::parse(stringA)) == *(ShuntingYardParser::parse(stringB)));
    REQUIRE(*(ShuntingYardParser::parse(stringA)) == *(ShuntingYardParser::parse(stringC)));

    stringA = "(whileA+2-whileC)*(4/whileE)%whileF";
    stringB = "((whileA+2)-whileC)*(4/whileE)%whileF";
    // The 2 strings are not equals but should produce the same tree
    REQUIRE(*(ShuntingYardParser::parse(stringA)) == *(ShuntingYardParser::parse(stringB)));

    stringA = "x+y+z";
    stringB = "x+y";
    REQUIRE_FALSE(*(ShuntingYardParser::parse(stringA)) == *(ShuntingYardParser::parse(stringB)));
}
