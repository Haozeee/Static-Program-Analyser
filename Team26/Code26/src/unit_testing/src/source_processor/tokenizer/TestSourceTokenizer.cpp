#include <string>
#include <sstream>
#include <vector>
#include "catch.hpp"
#include "source_processor/tokenizer/Tokenizer.h"

TEST_CASE("Test readSpecialChar") {
    SECTION("Invalid Special Char") {
        std::string inputString = "procedure procedure1 { \n x = @; }";
        std::istream* istream = new std::stringstream(inputString);
        Tokenizer sourceTokenizer = Tokenizer(istream);

        REQUIRE_THROWS(sourceTokenizer.tokenize());
        delete istream;
    };

    SECTION("Invalid Logical Op") {
        std::string inputString = "procedure procedure1 { \n >|; }";
        std::istream* istream = new std::stringstream(inputString);
        Tokenizer sourceTokenizer = Tokenizer(istream);

        REQUIRE_THROWS(sourceTokenizer.tokenize());
        delete istream;
    };
}

TEST_CASE("Test SourceTokenize") {
    SECTION("valid Source") {
        std::string inputString = "procedure procedure1 { x = 1 ; }";
        std::istream* istream = new std::stringstream(inputString);
        Tokenizer sourceTokenizer = Tokenizer(istream);

        auto tokens = sourceTokenizer.tokenize();
        REQUIRE(tokens[0]->getValue() == "procedure");
        REQUIRE(tokens[1]->getValue() == "procedure1");
        REQUIRE(tokens[2]->getValue() == "{");
        REQUIRE(tokens[3]->getValue() == "x");
        REQUIRE(tokens[4]->getValue() == "=");
        REQUIRE(tokens[5]->getValue() == "1");
        REQUIRE(tokens[6]->getValue() == ";");
        REQUIRE(tokens[7]->getValue() == "}");
        REQUIRE(tokens[8]->getValue() == "EOF");
        delete istream;
    }
    SECTION("invalid Source") {
        std::string inputString = "procedureprocedure1{x=1;}";
        std::istream* istream = new std::stringstream(inputString);
        Tokenizer sourceTokenizer = Tokenizer(istream);

        auto tokens = sourceTokenizer.tokenize();
        REQUIRE(tokens[0]->getValue() == "procedureprocedure1");
        REQUIRE_FALSE(tokens[1]->getValue() == "EOF");
        REQUIRE(tokens[1]->getValue() == "{");
        REQUIRE(tokens[2]->getValue() == "x");
        REQUIRE(tokens[3]->getValue() == "=");
        REQUIRE(tokens[4]->getValue() == "1");
        REQUIRE(tokens[7]->getValue() == "EOF");
        delete istream;
    }
}