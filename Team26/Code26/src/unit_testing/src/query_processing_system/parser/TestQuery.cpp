#include "catch.hpp"
#include <memory>
#include <vector>
#include "common/tokenizer/token/NameToken.h"
#include "common/tokenizer/token/SpecialCharToken.h"
#include "common/tokenizer/token/EndOfFileToken.h"
#include "common/tokenizer/token/StringExpressionToken.h"
#include "query_processing_system/parser/QueryParser.h"
#include "query_processing_system/parser/Query.h"

TEST_CASE("Query Class") {
    std::vector<std::shared_ptr<Token>> tokens{
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("v"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Follows"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<StringExpressionToken>(("xyz")),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
    };

    auto *query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    auto allClauses = query->getAllClauses();
    REQUIRE(allClauses.size() == 1);

    delete query;
}