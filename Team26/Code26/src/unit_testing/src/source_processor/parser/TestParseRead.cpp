#include "catch.hpp"
#include "TestSourceParserUtil.h"
#include "source_processor/parser/Parser.h"


TEST_CASE("Parser Read") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("single Read: missing keyword") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single Read: missing variable name") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single Read: missing semicolon") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single Read") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);

        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
        CHECK(stmtNode->stmtIndex == 1);
        REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);

        ReadNode* readNode;
        REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
        CHECK(readNode->varName == "xyz");
    }

    SECTION("double Read same Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 2);

        SECTION("first Read") {
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 1);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);

            ReadNode* readNode;
            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
            CHECK(readNode->varName == "xyz");
        }

        SECTION("second Read") {
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
            CHECK(stmtNode->stmtIndex == 2);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);

            ReadNode* readNode;
            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
            CHECK(readNode->varName == "abc");
        }
    }

    SECTION("double Read different Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 2);

        SECTION("first Procedure") {
            REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 1);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);

            ReadNode* readNode;
            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
            CHECK(readNode->varName == "xyz");
        }

        SECTION("second Procedure") {
            REQUIRE(programNode->procedureList[1]->stmtListNode->stmtList.size() >= 1);
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[1]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 2);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);

            ReadNode* readNode;
            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
            CHECK(readNode->varName == "abc");
        }
    }
}
