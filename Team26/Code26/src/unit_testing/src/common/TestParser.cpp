#include "TestParser.h"
#include "common/tokenizer/token/NameToken.h"
#include "common/tokenizer/token/SpecialCharToken.h"
#include "common/tokenizer/token/IntegerToken.h"
#include "common/tokenizer/token/EndOfFileToken.h"

TestParser::TestParser(std::vector<std::shared_ptr<Token>> tokens) : AbstractParser(tokens) {
}

bool TestParser::hasNext() {
    return AbstractParser::hasNext();
}

bool TestParser::isTypeOf(TokenType type) {
    return AbstractParser::isTypeOf(type);
}

bool TestParser::isValueOf(const std::string &value) {
    return AbstractParser::isValueOf(value);
}

std::shared_ptr<Token> TestParser::getNext() {
    return AbstractParser::getNext();
}

std::shared_ptr<Token> TestParser::parseNext(TokenType type) {
    return AbstractParser::parseNext(type);
}

std::shared_ptr<Token> TestParser::parseNext(const std::string& value) {
    return AbstractParser::parseNext(value);
}

void TestParser::parse() {

}

TEST_CASE("Test hasNext") {
    SECTION("TRUTHY") {
        std::vector<std::shared_ptr<Token>> tokens;

        std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
        std::shared_ptr<Token> token2 = std::make_shared<NameToken>("procedure1");
        std::shared_ptr<Token> token3 = std::make_shared<SpecialCharToken>("{");
        std::shared_ptr<NameToken> token4 = std::make_shared<NameToken>("x");
        std::shared_ptr<Token> token5 = std::make_shared<SpecialCharToken>("=");
        std::shared_ptr<Token> token6 = std::make_shared<IntegerToken>("1");
        std::shared_ptr<Token> token7 = std::make_shared<SpecialCharToken>("}");
        std::shared_ptr<Token> token8 = std::make_shared<EndOfFileToken>();

        tokens.push_back(token1);
        tokens.push_back(token2);
        tokens.push_back(token3);
        tokens.push_back(token4);
        tokens.push_back(token5);
        tokens.push_back(token6);
        tokens.push_back(token7);
        tokens.push_back(token8);

        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

        REQUIRE(testParser->hasNext());
    }

    SECTION("FALSY") {
        std::vector<std::shared_ptr<Token>> tokens;
        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);
        REQUIRE_FALSE(!(testParser->hasNext()));
    }
}

TEST_CASE("Test isTypeOf") {
    SECTION("TRUTHY") {
        std::vector<std::shared_ptr<Token>> tokens;
        std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
        tokens.push_back(token1);

        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

        REQUIRE(testParser->isTypeOf(TokenType::TOKEN_NAME));

    }
    SECTION("FALSY") {
        std::vector<std::shared_ptr<Token>> tokens;
        std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
        tokens.push_back(token1);

        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

        REQUIRE_FALSE(testParser->isTypeOf(TokenType::TOKEN_END_OF_FILE));
    }
}

TEST_CASE("Test isValueOf") {
    SECTION("TRUTHY") {
        std::vector<std::shared_ptr<Token>> tokens;
        std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
        tokens.push_back(token1);

        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

        REQUIRE(testParser->isValueOf("procedure"));

    }
    SECTION("FALSY") {
        std::vector<std::shared_ptr<Token>> tokens;
        std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
        tokens.push_back(token1);

        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

        REQUIRE_FALSE(testParser->isValueOf(""));
    }
}

TEST_CASE("Test getNext") {
    std::vector<std::shared_ptr<Token>> tokens;

    std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
    std::shared_ptr<Token> token2 = std::make_shared<NameToken>("procedure1");
    std::shared_ptr<Token> token3 = std::make_shared<SpecialCharToken>("{");
    std::shared_ptr<NameToken> token4 = std::make_shared<NameToken>("x");
    std::shared_ptr<Token> token5 = std::make_shared<SpecialCharToken>("=");
    std::shared_ptr<Token> token6 = std::make_shared<IntegerToken>("1");
    std::shared_ptr<Token> token7 = std::make_shared<SpecialCharToken>("}");
    std::shared_ptr<Token> token8 = std::make_shared<EndOfFileToken>();

    tokens.push_back(token1);
    tokens.push_back(token2);
    tokens.push_back(token3);
    tokens.push_back(token4);
    tokens.push_back(token5);
    tokens.push_back(token6);
    tokens.push_back(token7);
    tokens.push_back(token8);

    std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

    REQUIRE(testParser->getNext() == token1);
    REQUIRE(testParser->getNext() == token2);
    REQUIRE(testParser->getNext() == token3);
    REQUIRE(testParser->getNext() == token4);
    REQUIRE(testParser->getNext() == token5);
    REQUIRE(testParser->getNext() == token6);
    REQUIRE(testParser->getNext() == token7);
    REQUIRE(testParser->getNext() == token8);
}

TEST_CASE("Test parseNext") {
    SECTION("Get Next by Type") {
        std::vector<std::shared_ptr<Token>> tokens;

        std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
        std::shared_ptr<Token> token2 = std::make_shared<NameToken>("procedure1");
        std::shared_ptr<Token> token3 = std::make_shared<SpecialCharToken>("{");

        tokens.push_back(token1);
        tokens.push_back(token2);
        tokens.push_back(token3);

        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

        REQUIRE(testParser->parseNext(TokenType::TOKEN_NAME) == token1);
        REQUIRE_THROWS(testParser->parseNext(TokenType::TOKEN_END_OF_FILE) == token3);
    }
    SECTION("Get Next by Value") {
        std::vector<std::shared_ptr<Token>> tokens;

        std::shared_ptr<Token> token1 = std::make_shared<NameToken>("procedure");
        std::shared_ptr<Token> token2 = std::make_shared<NameToken>("procedure1");

        tokens.push_back(token1);
        tokens.push_back(token2);

        std::unique_ptr<TestParser> testParser = std::make_unique<TestParser>(tokens);

        REQUIRE(testParser->parseNext("procedure") == token1);
        REQUIRE_THROWS(testParser->parseNext("") == token2);
    }
}