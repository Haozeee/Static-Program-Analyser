#include "catch.hpp"
#include <memory>
#include <vector>
#include "query_processing_system/QueryTokenizer.h"
#include "common/tokenizer/token/Token.h"
#include "common/tokenizer/token/NameToken.h"
#include "common/tokenizer/token/IntegerToken.h"
#include "common/tokenizer/token/SpecialCharToken.h"
#include "common/tokenizer/token/EndOfFileToken.h"
#include "common/tokenizer/token/StringExpressionToken.h"

auto ptrComparisonPredicate = [](const auto &item1, const auto &item2) {
    return (*item1) == (*item2);
};

TEST_CASE("Test Queries") {
    auto testQuery = "while w; assign a;\nSelect w such that Parent(w,a)";
    QueryTokenizer tokenizer = QueryTokenizer(testQuery);
    auto testTokens = tokenizer.tokenize();
    std::vector<std::shared_ptr<Token>> expectedToken {
            std::make_shared<NameToken>("while"),
            std::make_shared<NameToken>("w"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("w"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Parent"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("w"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>()
    };
    REQUIRE(std::equal(testTokens.begin(), testTokens.end(), expectedToken.begin(), expectedToken.end(), ptrComparisonPredicate));
}

TEST_CASE("Test Queries With Inverted Commas") {
    auto testQuery = "assign a;\nSelect a such that Modifies(a,\"x1\")";
    QueryTokenizer tokenizer = QueryTokenizer(testQuery);
    auto testTokens = tokenizer.tokenize();
    std::vector<std::shared_ptr<Token>> expectedToken {
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("a"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Modifies"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>("'"),
            std::make_shared<StringExpressionToken>("x1"),
            std::make_shared<SpecialCharToken>("'"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>()
    };
    REQUIRE(std::equal(testTokens.begin(), testTokens.end(), expectedToken.begin(), expectedToken.end(), ptrComparisonPredicate));
}

TEST_CASE("Test Queries With Integers") {
    auto testQuery = "assign a;\nSelect a such that Parent(2,6)";
    QueryTokenizer tokenizer = QueryTokenizer(testQuery);
    auto testTokens = tokenizer.tokenize();
    std::vector<std::shared_ptr<Token>> expectedToken {
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("a"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Parent"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<IntegerToken>("2"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<IntegerToken>("6"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>()
    };
    REQUIRE(std::equal(testTokens.begin(), testTokens.end(), expectedToken.begin(), expectedToken.end(), ptrComparisonPredicate));
}

TEST_CASE("Test Queries With Wildcard") {
    auto testQuery = "assign a;\nSelect a such that Modifies(a,_)";
    QueryTokenizer tokenizer = QueryTokenizer(testQuery);
    auto testTokens = tokenizer.tokenize();
    std::vector<std::shared_ptr<Token>> expectedToken {
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("a"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Modifies"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>("_"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>()
    };
    REQUIRE(std::equal(testTokens.begin(), testTokens.end(), expectedToken.begin(), expectedToken.end(), ptrComparisonPredicate));
}

TEST_CASE("Test Queries With Star Clause") {
    auto testQuery = "assign a;\nSelect a such that Follows*(a,_)";
    QueryTokenizer tokenizer = QueryTokenizer(testQuery);
    auto testTokens = tokenizer.tokenize();
    std::vector<std::shared_ptr<Token>> expectedToken {
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("a"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Follows"),
            std::make_shared<SpecialCharToken>("*"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>("_"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>()
    };
    REQUIRE(std::equal(testTokens.begin(), testTokens.end(), expectedToken.begin(), expectedToken.end(), ptrComparisonPredicate));
}
