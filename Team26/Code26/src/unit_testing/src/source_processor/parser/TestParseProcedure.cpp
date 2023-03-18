#include "catch.hpp"
#include "TestSourceParserUtil.h"
#include "source_processor/parser/SourceParser.h"

TEST_CASE("Parser Procedure") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("empty Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single procedure: missing keyword") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single procedure: missing procedure name") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single procedure: missing start braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single procedure: missing end braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(SourceParser(tokens).parse());

        auto parser = SourceParser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        CHECK(programNode->procedureList[0]->procedureName == "proc");
        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);

        std::vector<std::shared_ptr<StmtNode>> stmtList =
                programNode->procedureList[0]->stmtListNode->stmtList;
        std::shared_ptr<StmtNode> stmtNode = stmtList.at(0);
        CHECK(stmtList.at(0)->stmtIndex == 1);
        REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_READ);
    }

    SECTION("double procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(SourceParser(tokens).parse());

        auto parser = SourceParser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 2);

        SECTION("first procedure") {
            CHECK(programNode->procedureList[0]->procedureName == "proc1");
            REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);

            std::vector<std::shared_ptr<StmtNode>> stmtList =
                    programNode->procedureList[0]->stmtListNode->stmtList;
            std::shared_ptr<StmtNode> stmtNode = stmtList.at(0);
            CHECK(stmtList.at(0)->stmtIndex == 1);
            REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_READ);
        }

        SECTION("second procedure") {
            CHECK(programNode->procedureList[1]->procedureName == "proc2");
            REQUIRE(programNode->procedureList[1]->stmtListNode->stmtList.size() == 1);

            std::vector<std::shared_ptr<StmtNode>> stmtList =
                    programNode->procedureList[1]->stmtListNode->stmtList;
            std::shared_ptr<StmtNode> stmtNode = stmtList.at(0);
            CHECK(stmtList.at(0)->stmtIndex == 2);
            REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_PRINT);
        }
    }
}
