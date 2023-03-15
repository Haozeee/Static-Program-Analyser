#include "catch.hpp"
#include <memory>
#include <vector>
#include "common/tokenizer/token/NameToken.h"
#include "common/tokenizer/token/SpecialCharToken.h"
#include "common/tokenizer/token/EndOfFileToken.h"
#include "common/tokenizer/token/StringExpressionToken.h"
#include "common/tokenizer/token/IntegerToken.h"
#include "query_processing_system/parser/QueryParser.h"
#include "query_processing_system/QueryValidator.h"
#include "query_processing_system/QueryTokenizer.h"

TEST_CASE("Duplicate Synonyms in Declaration") {
    std::vector<std::shared_ptr<Token>> tokens{
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("v"),
            std::make_shared<EndOfFileToken>(),
    };

    Query *query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    QueryValidator validator = QueryValidator(query);
    REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
    delete query;
}

TEST_CASE("Undeclared Synonym in Select Clause") {
    std::vector<std::shared_ptr<Token>> tokens{
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("p"),
            std::make_shared<EndOfFileToken>(),
    };

    Query *query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    QueryValidator validator = QueryValidator(query);
    REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
    delete query;
}

TEST_CASE("Misspelled PQL Language") {
    std::vector<std::shared_ptr<Token>> tokens{
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("p"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("follows"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<StringExpressionToken>(("xyz")),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
    };

    Query *query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS_AS(parser.parse(), QuerySyntaxException);
    delete query;
}

TEST_CASE("Validate Such That Clause") {
    SECTION("Follows") {
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

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("FollowsT") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Follows"),
                std::make_shared<SpecialCharToken>("*"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("xyz")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>("123"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("Parent") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Parent"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("xyz")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>("123"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("ParentT") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Parent"),
                std::make_shared<SpecialCharToken>("*"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("xyz")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>("123"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("UsesS") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("stmt"),
                std::make_shared<NameToken>("stmt"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("stmt"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Uses"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("stmt"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>(("456")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("ModifiesS") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("stmt"),
                std::make_shared<NameToken>("stmt"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("stmt"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Modifies"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("stmt"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>(("456")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("UsesP") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("procedure"),
                std::make_shared<NameToken>("proc"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("proc"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Uses"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("proc"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>(("456")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("ModifiesP") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("procedure"),
                std::make_shared<NameToken>("proc"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("proc"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Modifies"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("proc"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>(("456")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("Affects") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("constant"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("constant"),
                std::make_shared<NameToken>("a1"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("a"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Affects"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<NameToken>("a1"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("AffectsT") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("while"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("while"),
                std::make_shared<NameToken>("a1"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("a"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Affects"),
                std::make_shared<SpecialCharToken>("*"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<NameToken>("a1"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("Calls") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("stmt"),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("stmt"),
                std::make_shared<NameToken>("p1"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("a"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Calls"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<NameToken>("p1"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("CallsT") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("if"),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("if"),
                std::make_shared<NameToken>("p1"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("a"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Calls"),
                std::make_shared<SpecialCharToken>("*"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<NameToken>("p1"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("Next") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("r"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("pr"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("a"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Next"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("r"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<NameToken>("pr"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }

    SECTION("NextT") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("stmt"),
                std::make_shared<NameToken>("ifs"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("c"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("a"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Next"),
                std::make_shared<SpecialCharToken>("*"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("ifs"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<NameToken>("c"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS_AS(validator.validateQuery(), QuerySemanticException);
        delete query;
    }
}

TEST_CASE("Validate Pattern Clause") {
    SECTION("While Pattern Clause") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("while"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS(validator.validateQuery());
        delete query;
    }

    SECTION("If Pattern Clause") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("if"),
                std::make_shared<NameToken>("ifs"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("ifs"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS(validator.validateQuery());
        delete query;
    }

    SECTION("Invalid Left Argument Type") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("assign"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<IntegerToken>("123"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS(validator.validateQuery());
        delete query;
    }

    SECTION("Invalid Left Design Entity") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("constant"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("assign"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        Query *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        QueryValidator validator = QueryValidator(query);
        REQUIRE_THROWS(validator.validateQuery());
        delete query;
    }
}

TEST_CASE("Validate With Clause") {
    std::string string = "constant a; call s;"
                         "Select <a, s> with a.value = s.procName";
    QueryTokenizer tokenizer = QueryTokenizer(string);
    std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

    auto *query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    QueryValidator validator = QueryValidator(query);
    REQUIRE_THROWS(validator.validateQuery());
    delete query;
}

TEST_CASE("Select BOOLEAN") {
    std::string string = "variable v;"
                         "Select BOOLEAN";
    QueryTokenizer tokenizer = QueryTokenizer(string);
    std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    QueryValidator validator = QueryValidator(query);
    validator.validateQuery();
    delete query;
}
