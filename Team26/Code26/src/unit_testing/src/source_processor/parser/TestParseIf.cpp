#include "catch.hpp"
#include "TestSourceParserUtil.h"
#include "source_processor/parser/Parser.h"

TEST_CASE("Parser If") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("single If: missing keyword") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num3"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single If: missing start_braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "then"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num3"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single If: missing end_braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single If") {

    }

    SECTION("nested If same Procedure") {

    }

    // TODO(oviya): add unit test for multiple procedures in upcoming sprint.
}
