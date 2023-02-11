#include "TestTokenizer.h"
#include <memory>

TestTokenizer::TestTokenizer(std::istream *stream) : AbstractTokenizer(stream) {}

TestTokenizer::TestTokenizer(const std::string &query) : AbstractTokenizer(query) {}

std::vector<std::shared_ptr<Token>> TestTokenizer::tokenize() {
    return {};
}

void TestTokenizer::readSpecialChar() {
}

char TestTokenizer::nextChar() {
    return AbstractTokenizer::nextChar();
}

char TestTokenizer::peekChar() {
    return AbstractTokenizer::peekChar();
}

void TestTokenizer::readName() {
    return AbstractTokenizer::readName();
}

void TestTokenizer::readInteger() {
    return AbstractTokenizer::readInteger();
}

std::string TestTokenizer::getCurrentToken() {
    return AbstractTokenizer::getCurrentToken();
}

TEST_CASE("Test peekChar") {
    std::unique_ptr<TestTokenizer> testTokenizer = std::make_unique<TestTokenizer>("test");
    REQUIRE(testTokenizer->peekChar() == 't');
}

TEST_CASE("Test nextChar") {
    std::unique_ptr<TestTokenizer> testTokenizer = std::make_unique<TestTokenizer>("test");
    REQUIRE(testTokenizer->nextChar() == 't');
    REQUIRE_FALSE(testTokenizer->nextChar() == 's');
    REQUIRE(testTokenizer->nextChar() == 's');
    REQUIRE_FALSE(testTokenizer->nextChar() == 'a');
}

TEST_CASE("Test readName") {
    std::unique_ptr<TestTokenizer> testTokenizer = std::make_unique<TestTokenizer>("test!123abc");
    testTokenizer->readName();
    REQUIRE_FALSE(testTokenizer->getCurrentToken() == "test!123");
    REQUIRE(testTokenizer->getCurrentToken() == "test");
}

TEST_CASE("Test readInteger") {
    SECTION("Basic Integer Input") {
        std::unique_ptr<TestTokenizer> testTokenizer = std::make_unique<TestTokenizer>("1234");
        testTokenizer->readInteger();
        REQUIRE(testTokenizer->getCurrentToken() == "1234");
    }
    SECTION("Leading Zeros Exception") {
        std::unique_ptr<TestTokenizer> testTokenizer = std::make_unique<TestTokenizer>("00001");
        REQUIRE_THROWS(testTokenizer->readInteger());
    }
}


