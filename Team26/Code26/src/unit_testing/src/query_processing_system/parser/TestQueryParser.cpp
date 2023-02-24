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

    Query *query = new Query();
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

    for (auto const item: *query->getSelectClause()->getSelectClauseItems()) {
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

        Query* query = new Query();
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

        Query* query = new Query();
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

        Query* query = new Query();
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
            std::make_shared<SpecialCharToken>("("),
            std::make_shared<NameToken>("w"),
            std::make_shared<SpecialCharToken>(","),
            std::make_shared<IntegerToken>(("456")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
        };

        Query* query = new Query();
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

        Query* query = new Query();
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

        Query* query = new Query();
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
}

TEST_CASE("Pattern Clause") {
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

    Query* query = new Query();
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
        REQUIRE(right.getExpression() == "x+y");
    }
    delete query;
}

TEST_CASE("Invalid Pattern Clause") {
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
            std::make_shared<StringExpressionToken>(("x+")),
            std::make_shared<SpecialCharToken>(("'")),
            std::make_shared<SpecialCharToken>(("_")),
            std::make_shared<SpecialCharToken>(")"),
            std::make_shared<EndOfFileToken>(),
    };
    Query* query = new Query();
    QueryParser parser = QueryParser(tokens, query);
    REQUIRE_THROWS(parser.parse());
    delete query;
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

    Query* query = new Query();
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
