#include "catch.hpp"
#include "TestSourceParserUtil.h"
#include "source_processor/parser/Parser.h"

TEST_CASE("Parser Call") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("single Call: missing keyword") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single Call: missing variable name") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single Call: missing semicolon") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

        // TODO(oviya): add call procedure name verification in upcoming milestone.

    SECTION("single Call") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(!programNode->procedureList[0]->stmtListNode->stmtList.empty());

        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
        CHECK(stmtNode->stmtIndex == 1);
        REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);

        CallNode* callNode;
        REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
        CHECK(callNode->procedureName == "xyz");
    }

    SECTION("double Call same Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
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

        SECTION("first Call") {
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 1);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);

            CallNode* callNode;
            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
            CHECK(callNode->procedureName == "xyz");
        }

        SECTION("second Call") {
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
            CHECK(stmtNode->stmtIndex == 2);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);

            CallNode* callNode;
            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
            CHECK(callNode->procedureName == "abc");
        }
    }

    SECTION("double Call different Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
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
            REQUIRE(!programNode->procedureList[0]->stmtListNode->stmtList.empty());
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 1);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);

            CallNode* callNode;
            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
            CHECK(callNode->procedureName == "xyz");
        }

        SECTION("second Procedure") {
            REQUIRE(!programNode->procedureList[1]->stmtListNode->stmtList.empty());
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[1]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 2);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);

            CallNode* callNode;
            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
            CHECK(callNode->procedureName == "abc");
        }
    }
}
