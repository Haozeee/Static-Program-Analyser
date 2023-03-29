#include "catch.hpp"
#include <string>
#include <memory>
#include <vector>
#include "common/tokenizer/token/NameToken.h"
#include "common/tokenizer/token/SpecialCharToken.h"
#include "common/tokenizer/token/EndOfFileToken.h"
#include "common/tokenizer/token/StringExpressionToken.h"
#include "common/tokenizer/token/IntegerToken.h"
#include "query_processing_system/parser/QueryParser.h"
#include "query_processing_system/QueryTokenizer.h"

TEST_CASE("Basic Declaration") {
    std::vector<std::shared_ptr<Token>> tokens{
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("v1"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("procedure"),
            std::make_shared<NameToken>("p"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("p1"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("stmt"),
            std::make_shared<NameToken>("s"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("s1"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("a1"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("constant"),
            std::make_shared<NameToken>("c"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("c1"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("while"),
            std::make_shared<NameToken>("w"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("w1"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("v"),
            std::make_shared<EndOfFileToken>(),
    };

    auto *query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    REQUIRE(query->getDeclarations()[0]->getSynonym() == Synonym("v"));
    REQUIRE(toString(query->getDeclarations()[0]->getDesignEntity()) == "variable");

    REQUIRE(query->getDeclarations()[1]->getSynonym() == Synonym("v1"));
    REQUIRE(toString(query->getDeclarations()[1]->getDesignEntity()) == "variable");

    REQUIRE(query->getDeclarations()[2]->getSynonym() == Synonym("p"));
    REQUIRE(toString(query->getDeclarations()[2]->getDesignEntity()) == "procedure");

    REQUIRE(query->getDeclarations()[3]->getSynonym() == Synonym("p1"));
    REQUIRE(toString(query->getDeclarations()[3]->getDesignEntity()) == "procedure");

    REQUIRE(query->getDeclarations()[4]->getSynonym() == Synonym("s"));
    REQUIRE(toString(query->getDeclarations()[4]->getDesignEntity()) == "stmt");

    REQUIRE(query->getDeclarations()[5]->getSynonym() == Synonym("s1"));
    REQUIRE(toString(query->getDeclarations()[5]->getDesignEntity()) == "stmt");

    REQUIRE(query->getDeclarations()[6]->getSynonym() == Synonym("a"));
    REQUIRE(toString(query->getDeclarations()[6]->getDesignEntity()) == "assign");

    REQUIRE(query->getDeclarations()[7]->getSynonym() == Synonym("a1"));
    REQUIRE(toString(query->getDeclarations()[7]->getDesignEntity()) == "assign");

    REQUIRE(query->getDeclarations()[8]->getSynonym() == Synonym("c"));
    REQUIRE(toString(query->getDeclarations()[8]->getDesignEntity()) == "constant");

    REQUIRE(query->getDeclarations()[9]->getSynonym() == Synonym("c1"));
    REQUIRE(toString(query->getDeclarations()[9]->getDesignEntity()) == "constant");

    REQUIRE(query->getDeclarations()[10]->getSynonym() == Synonym("w"));
    REQUIRE(toString(query->getDeclarations()[10]->getDesignEntity()) == "while");

    REQUIRE(query->getDeclarations()[11]->getSynonym() == Synonym("w1"));
    REQUIRE(toString(query->getDeclarations()[11]->getDesignEntity()) == "while");

    for (auto const& item: *query->getSelectClauseItems()) {
        REQUIRE(SelectClause::getSynonym(item) == "v");
    }
    delete query;
}

TEST_CASE("Such That Clause") {
    SECTION("Follows") {
        std::vector<std::shared_ptr<Token>> tokens {
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "v");
            REQUIRE(left.getDesignEntity() == DesignEntity::VARIABLE);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::CHARACTERSTRING);
            REQUIRE(right.getValue() == "xyz");
            REQUIRE(right.getDesignEntity() == DesignEntity::NONE);
        }
        delete query;
    }

    SECTION("FollowsT") {
        std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("constant"),
            std::make_shared<NameToken>("c"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("c"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Follows"),
            std::make_shared<SpecialCharToken>("*"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<IntegerToken>("123"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("c"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::NUMBER);
            REQUIRE(left.getValue() == "123");
            REQUIRE(left.getDesignEntity() == DesignEntity::NONE);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(right.getValue() == "c");
            REQUIRE(right.getDesignEntity() == DesignEntity::CONSTANT);
        }
        delete query;
    }

    SECTION("Parent") {
        std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("a"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Parent"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>(("_")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "a");
            REQUIRE(left.getDesignEntity() == DesignEntity::ASSIGN);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::WILDCARD);
            REQUIRE(right.getValue() == "_");
            REQUIRE(right.getDesignEntity() == DesignEntity::NONE);
        }
        delete query;
    }

    SECTION("ParentT") {
        std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("while"),
            std::make_shared<NameToken>("w"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("w"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Parent"),
            std::make_shared<SpecialCharToken>("*"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("w"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<IntegerToken>(("456")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "w");
            REQUIRE(left.getDesignEntity() == DesignEntity::WHILE);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::NUMBER);
            REQUIRE(right.getValue() == "456");
            REQUIRE(right.getDesignEntity() == DesignEntity::NONE);
        }
        delete query;
    }

    SECTION("UsesS") {
        std::vector<std::shared_ptr<Token>> tokens {
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
            std::make_shared<SpecialCharToken>(("_")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "stmt");
            REQUIRE(left.getDesignEntity() == DesignEntity::STMT);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::WILDCARD);
            REQUIRE(right.getValue() == "_");
            REQUIRE(right.getDesignEntity() == DesignEntity::NONE);
        }
        delete query;
    }

    SECTION("ModifiesS") {
        std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("if"),
            std::make_shared<NameToken>("ifs"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("ifs"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Modifies"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("ifs"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<IntegerToken>("789"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "ifs");
            REQUIRE(left.getDesignEntity() == DesignEntity::IF);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::NUMBER);
            REQUIRE(right.getValue() == "789");
            REQUIRE(right.getDesignEntity() == DesignEntity::NONE);
        }
        delete query;
    }

    SECTION("UsesP") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("procedure"),
                std::make_shared<NameToken>("procedure"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("s"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Uses"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("procedure"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "procedure");
            REQUIRE(left.getDesignEntity() == DesignEntity::PROCEDURE);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::WILDCARD);
            REQUIRE(right.getValue() == "_");
            REQUIRE(right.getDesignEntity() == DesignEntity::NONE);
        }
        delete query;
    }

    SECTION("ModifiesP") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("procedure"),
                std::make_shared<NameToken>("proc"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("ifs"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Modifies"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("proc"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<IntegerToken>("789"),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "proc");
            REQUIRE(left.getDesignEntity() == DesignEntity::PROCEDURE);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::NUMBER);
            REQUIRE(right.getValue() == "789");
            REQUIRE(right.getDesignEntity() == DesignEntity::NONE);
        }
        delete query;
    }

    SECTION("Affects") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("assign"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("assign"),
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "a");
            REQUIRE(left.getDesignEntity() == DesignEntity::ASSIGN);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(right.getValue() == "a1");
            REQUIRE(right.getDesignEntity() == DesignEntity::ASSIGN);
        }
        delete query;
    }

    SECTION("AffectsT") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("assign"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("assign"),
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "a");
            REQUIRE(left.getDesignEntity() == DesignEntity::ASSIGN);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(right.getValue() == "a1");
            REQUIRE(right.getDesignEntity() == DesignEntity::ASSIGN);
        }
        delete query;
    }

    SECTION("Calls") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("procedure"),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("procedure"),
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "p");
            REQUIRE(left.getDesignEntity() == DesignEntity::PROCEDURE);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(right.getValue() == "p1");
            REQUIRE(right.getDesignEntity() == DesignEntity::PROCEDURE);
        }
        delete query;
    }

    SECTION("CallsT") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("procedure"),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("procedure"),
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "p");
            REQUIRE(left.getDesignEntity() == DesignEntity::PROCEDURE);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(right.getValue() == "p1");
            REQUIRE(right.getDesignEntity() == DesignEntity::PROCEDURE);
        }
        delete query;
    }

    SECTION("Next") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("read"),
                std::make_shared<NameToken>("r"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("print"),
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "r");
            REQUIRE(left.getDesignEntity() == DesignEntity::READ);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(right.getValue() == "pr");
            REQUIRE(right.getDesignEntity() == DesignEntity::PRINT);
        }
        delete query;
    }

    SECTION("NextT") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("if"),
                std::make_shared<NameToken>("ifs"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("call"),
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getSuchThatClauses()) {
            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "ifs");
            REQUIRE(left.getDesignEntity() == DesignEntity::IF);

            Argument right = item->getRightArg();
            REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(right.getValue() == "c");
            REQUIRE(right.getDesignEntity() == DesignEntity::CALL);
        }
        delete query;
    }
}

TEST_CASE("Pattern Clause") {
    SECTION("Assign Pattern Clause") {
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

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getPatternClause()) {
            Argument pattern = item->getPatternArg();
            REQUIRE(pattern.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(pattern.getValue() == "a");
            REQUIRE(pattern.getDesignEntity() == DesignEntity::ASSIGN);

            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "v");
            REQUIRE(left.getDesignEntity() == DesignEntity::VARIABLE);

            StringExpression right = item->getRightArg();
            REQUIRE(right.isWildCard() == false);
            REQUIRE(right.getExpression() == "x+y");
        }
        delete query;
    }

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
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getPatternClause()) {
            Argument pattern = item->getPatternArg();
            REQUIRE(pattern.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(pattern.getValue() == "w");
            REQUIRE(pattern.getDesignEntity() == DesignEntity::WHILE);

            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "v");
            REQUIRE(left.getDesignEntity() == DesignEntity::VARIABLE);

            StringExpression right = item->getRightArg();
            REQUIRE(right.isWildCard() == true);
        }
        delete query;
    }

    SECTION("If Pattern Clause") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("if"),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        for (auto const item : query->getPatternClause()) {
            Argument pattern = item->getPatternArg();
            REQUIRE(pattern.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(pattern.getValue() == "i");
            REQUIRE(pattern.getDesignEntity() == DesignEntity::IF);

            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(left.getValue() == "v");
            REQUIRE(left.getDesignEntity() == DesignEntity::VARIABLE);

            StringExpression right = item->getRightArg();
            REQUIRE(right.isWildCard() == true);
        }
        delete query;
    }
}

TEST_CASE("Invalid Pattern Clause") {
    SECTION("Invalid Assign Pattern Clause") {
        std::vector<std::shared_ptr<Token>> tokens{
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
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }

    SECTION("Invalid While Pattern Clause") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("while"),
                std::make_shared<NameToken>("w"),
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
                std::make_shared<StringExpressionToken>(("x+")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }

    SECTION("Invalid If Pattern Clause") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("if"),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }

    SECTION("Multiple Pattern Clause") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("if"),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<NameToken>("and"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("i"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("a+b")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }

    SECTION("Invalid Pattern Clause Design Entity") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v1"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("v1"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }

    SECTION("Invalid While Pattern Clause Not )") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("while"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<EndOfFileToken>(),
        };

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }

    SECTION("Invalid While Pattern Clause Two Arguments") {
        std::vector<std::shared_ptr<Token>> tokens{
                std::make_shared<NameToken>("while"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("v"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("x+y")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }
}

TEST_CASE("With Clause") {
    SECTION("Valid With Clause and BOOLEAN") {
        std::string string = "assign a; stmt s;"
                             "Select BOOLEAN with a.stmt# = 12";
        QueryTokenizer tokenizer = QueryTokenizer(string);
        std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        AttributeReference leftAttrRef = *new AttributeReference(DesignEntity::ASSIGN, "a", "stmt#");
        Reference leftRef = Reference::createReference(leftAttrRef);
        Reference rightRef = Reference::createReference(12);

        for (auto const item: query->getWithClause()) {
            Reference left = item->getLeftRef();
            REQUIRE(left == leftRef);

            Reference right = item->getRightRef();
            REQUIRE(right == rightRef);
        }

        delete query;
    }

    SECTION("Valid With Clause and Tuple") {
        std::string string = "assign a; stmt s;"
                             "Select <a, s> with a.stmt# = s.stmt#";
        QueryTokenizer tokenizer = QueryTokenizer(string);
        std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        auto firstSyn = *std::get<std::shared_ptr<Synonym>>(query->getSelectClauseItems()->front());
        REQUIRE(firstSyn.getIdent() == "a");

        auto secondSyn = *std::get<std::shared_ptr<Synonym>>(query->getSelectClauseItems()->back());
        REQUIRE(secondSyn.getIdent() == "s");

        AttributeReference leftAttrRef = *new AttributeReference(DesignEntity::ASSIGN, "a", "stmt#");
        AttributeReference rightAttrRef = *new AttributeReference(DesignEntity::STMT, "s", "stmt#");
        Reference leftRef = Reference::createReference(leftAttrRef);
        Reference rightRef = Reference::createReference(rightAttrRef);

        for (auto const item: query->getWithClause()) {
            Reference left = item->getLeftRef();
            REQUIRE(left == leftRef);

            Reference right = item->getRightRef();
            REQUIRE(right == rightRef);
        }

        delete query;
    }

    SECTION("Invalid Attribute Reference Type Mismatch") {
        std::string string = "assign a; stmt s;"
                             "Select <a, s> with a.stmt# = s";
        QueryTokenizer tokenizer = QueryTokenizer(string);
        std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }

    SECTION("Invalid Attribute Reference Ident") {
        std::string string = "assign a; stmt s;"
                             "Select <a, s> with \"a+1\" = s";
        QueryTokenizer tokenizer = QueryTokenizer(string);
        std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        REQUIRE_THROWS(parser.parse());

        delete query;
    }
}

TEST_CASE("Such That and Pattern Clause") {
    std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("assign"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("v"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Modifies"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<NameToken>("pattern"),
            std::make_shared<NameToken>("a"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>(("_")),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<StringExpressionToken>(("a+b")),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<SpecialCharToken>(("_")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
    };

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    for (auto const item : query->getSuchThatClauses()) {
        Argument left = item->getLeftArg();
        REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(left.getValue() == "a");
        REQUIRE(left.getDesignEntity() == DesignEntity::ASSIGN);

        Argument right = item->getRightArg();
        REQUIRE(right.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(right.getValue() == "v");
        REQUIRE(right.getDesignEntity() == DesignEntity::VARIABLE);
    }

    for (auto const item : query->getPatternClause()) {
        Argument pattern = item->getPatternArg();
        REQUIRE(pattern.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(pattern.getValue() == "a");
        REQUIRE(pattern.getDesignEntity() == DesignEntity::ASSIGN);

        Argument left = item->getLeftArg();
        REQUIRE(left.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(left.getValue() == "v");
        REQUIRE(left.getDesignEntity() == DesignEntity::VARIABLE);

        StringExpression right = item->getRightArg();
        REQUIRE(right.getExpression() == "a+b");
    }
    delete query;
}

TEST_CASE("Multi Clause") {
    SECTION("Such That and Pattern") {
        std::vector<std::shared_ptr<Token>> tokens {
                std::make_shared<NameToken>("while"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("assign"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("variable"),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("procedure"),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(";"),
                std::make_shared<NameToken>("Select"),
                std::make_shared<NameToken>("a"),
                std::make_shared<NameToken>("such"),
                std::make_shared<NameToken>("that"),
                std::make_shared<NameToken>("Modifies"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("abc")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<NameToken>("and"),
                std::make_shared<NameToken>("Calls"),
                std::make_shared<SpecialCharToken>("*"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("p"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("xyz")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("a"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("a+b")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<NameToken>("pattern"),
                std::make_shared<NameToken>("w"),
                std::make_shared<SpecialCharToken>("("),
                std::make_shared<NameToken>("v"),
                std::make_shared<SpecialCharToken>(","),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<StringExpressionToken>(("c+d")),
                std::make_shared<SpecialCharToken>(("'")),
                std::make_shared<SpecialCharToken>(("_")),
                std::make_shared<SpecialCharToken>(")"),
                std::make_shared<EndOfFileToken>(),
        };

        auto* query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        auto firstSuchThatClause = query->getSuchThatClauses().front();
        Argument firstLeft = firstSuchThatClause->getLeftArg();
        REQUIRE(firstLeft.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(firstLeft.getValue() == "a");
        REQUIRE(firstLeft.getDesignEntity() == DesignEntity::ASSIGN);

        Argument firstRight = firstSuchThatClause->getRightArg();
        REQUIRE(firstRight.getArgumentType() == ArgumentType::CHARACTERSTRING);
        REQUIRE(firstRight.getValue() == "abc");
        REQUIRE(firstRight.getDesignEntity() == DesignEntity::NONE);

        auto secondSuchThatClause = query->getSuchThatClauses().back();
        Argument secondLeft = secondSuchThatClause->getLeftArg();
        REQUIRE(secondLeft.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(secondLeft.getValue() == "p");
        REQUIRE(secondLeft.getDesignEntity() == DesignEntity::PROCEDURE);

        Argument secondRight = secondSuchThatClause->getRightArg();
        REQUIRE(secondRight.getArgumentType() == ArgumentType::CHARACTERSTRING);
        REQUIRE(secondRight.getValue() == "xyz");
        REQUIRE(secondRight.getDesignEntity() == DesignEntity::NONE);

        auto firstPatternClause = query->getPatternClause().front();
        Argument firstPattern = firstPatternClause->getPatternArg();
        REQUIRE(firstPattern.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(firstPattern.getValue() == "a");
        REQUIRE(firstPattern.getDesignEntity() == DesignEntity::ASSIGN);

        Argument firstPatternLeft = firstPatternClause->getLeftArg();
        REQUIRE(firstPatternLeft.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(firstPatternLeft.getValue() == "v");
        REQUIRE(firstPatternLeft.getDesignEntity() == DesignEntity::VARIABLE);

        StringExpression firstPatternRight = firstPatternClause->getRightArg();
        REQUIRE(firstPatternRight.getExpression() == "a+b");

        auto secondPatternClause = query->getPatternClause().back();
        Argument secondPattern = secondPatternClause->getPatternArg();
        REQUIRE(secondPattern.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(secondPattern.getValue() == "w");
        REQUIRE(secondPattern.getDesignEntity() == DesignEntity::WHILE);

        Argument secondPatternLeft = secondPatternClause->getLeftArg();
        REQUIRE(secondPatternLeft.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(secondPatternLeft.getValue() == "v");
        REQUIRE(secondPatternLeft.getDesignEntity() == DesignEntity::VARIABLE);

        StringExpression secondPatternRight = secondPatternClause->getRightArg();
        REQUIRE(secondPatternRight.getExpression() == "c+d");

        delete query;
    }

    SECTION("Such That, Pattern and With Clauses") {
        std::string string = "assign a; while w; stmt s;"
                             "Select <w, s> such that Parent* (w, a) and Next* (60, s) pattern a(\"x\", _) with a.stmt# = s.stmt#";
        QueryTokenizer tokenizer = QueryTokenizer(string);
        std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

        auto *query = new Query();
        QueryParser parser = QueryParser(tokens, query);
        parser.parse();

        auto firstSyn = *std::get<std::shared_ptr<Synonym>>(query->getSelectClauseItems()->front());
        REQUIRE(firstSyn.getIdent() == "w");

        auto secondSyn = *std::get<std::shared_ptr<Synonym>>(query->getSelectClauseItems()->back());
        REQUIRE(secondSyn.getIdent() == "s");

        auto firstSuchThatClause = query->getSuchThatClauses().front();
        Argument firstLeft = firstSuchThatClause->getLeftArg();
        REQUIRE(firstLeft.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(firstLeft.getValue() == "w");
        REQUIRE(firstLeft.getDesignEntity() == DesignEntity::WHILE);

        Argument firstRight = firstSuchThatClause->getRightArg();
        REQUIRE(firstRight.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(firstRight.getValue() == "a");
        REQUIRE(firstRight.getDesignEntity() == DesignEntity::ASSIGN);

        auto secondSuchThatClause = query->getSuchThatClauses().back();
        Argument secondLeft = secondSuchThatClause->getLeftArg();
        REQUIRE(secondLeft.getArgumentType() == ArgumentType::NUMBER);
        REQUIRE(secondLeft.getValue() == "60");
        REQUIRE(secondLeft.getDesignEntity() == DesignEntity::NONE);

        Argument secondRight = secondSuchThatClause->getRightArg();
        REQUIRE(secondRight.getArgumentType() == ArgumentType::SYNONYM);
        REQUIRE(secondRight.getValue() == "s");
        REQUIRE(secondRight.getDesignEntity() == DesignEntity::STMT);

        for (auto const item : query->getPatternClause()) {
            Argument pattern = item->getPatternArg();
            REQUIRE(pattern.getArgumentType() == ArgumentType::SYNONYM);
            REQUIRE(pattern.getValue() == "a");
            REQUIRE(pattern.getDesignEntity() == DesignEntity::ASSIGN);

            Argument left = item->getLeftArg();
            REQUIRE(left.getArgumentType() == ArgumentType::CHARACTERSTRING);
            REQUIRE(left.getValue() == "x");
            REQUIRE(left.getDesignEntity() == DesignEntity::NONE);

            StringExpression right = item->getRightArg();
            REQUIRE(right.isWildCard() == true);
        }

        AttributeReference leftAttrRef = *new AttributeReference(DesignEntity::ASSIGN, "a", "stmt#");
        AttributeReference rightAttrRef = *new AttributeReference(DesignEntity::STMT, "s", "stmt#");
        Reference leftRef = Reference::createReference(leftAttrRef);
        Reference rightRef = Reference::createReference(rightAttrRef);

        for (auto const item : query->getWithClause()) {
            Reference left = item->getLeftRef();
            REQUIRE(left == leftRef);

            Reference right = item->getRightRef();
            REQUIRE(right == rightRef);
        }

        delete query;
    }
}

TEST_CASE("Invalid Select Clause") {
    std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<IntegerToken>("12"),
            std::make_shared<EndOfFileToken>(),
    };

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS(parser.parse());

    delete query;
}

TEST_CASE("Edge Case: BOOLEAN in Attribute Reference") {
    std::string string = "variable BOOLEAN;"
                         "Select BOOLEAN.varName";
    QueryTokenizer tokenizer = QueryTokenizer(string);
    std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    parser.parse();

    for (auto const& item: *query->getSelectClauseItems()) {
        REQUIRE(SelectClause::getSynonym(item) == "BOOLEAN");
    }

    delete query;
}

TEST_CASE("Invalid Return Value") {
    std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<SpecialCharToken>("_"),
            std::make_shared<EndOfFileToken>(),
    };

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS(parser.parse());

    delete query;
}

TEST_CASE("Invalid Ident") {
    std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("BOOLEAN"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Modifies"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<StringExpressionToken>(("a+c")),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
    };

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS(parser.parse());

    delete query;
}

TEST_CASE("Invalid Argument") {
    std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<NameToken>("BOOLEAN"),
            std::make_shared<NameToken>("such"),
            std::make_shared<NameToken>("that"),
            std::make_shared<NameToken>("Modifies"),
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<EndOfFileToken>(),
    };

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS(parser.parse());

    delete query;
}

TEST_CASE("Invalid String Expression") {
    std::string string = "assign a;"
                         "Select a pattern a(a, \"x+\")";
    QueryTokenizer tokenizer = QueryTokenizer(string);
    std::vector<std::shared_ptr<Token>> tokens = tokenizer.tokenize();

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS_AS(parser.parse(), QuerySyntaxException);

    delete query;
}

TEST_CASE("Unexpected Ending Token") {
    std::vector<std::shared_ptr<Token>> tokens {
            std::make_shared<NameToken>("variable"),
            std::make_shared<NameToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<NameToken>("Select"),
            std::make_shared<IntegerToken>("v"),
            std::make_shared<SpecialCharToken>(";"),
            std::make_shared<EndOfFileToken>(),
    };

    auto* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS(parser.parse());

    delete query;
}