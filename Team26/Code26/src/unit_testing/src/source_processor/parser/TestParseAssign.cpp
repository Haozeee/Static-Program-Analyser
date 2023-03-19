#include "catch.hpp"
#include "TestSourceParserUtil.h"
#include "source_processor/parser/SourceParser.h"


TEST_CASE("Parser Assign") {
std::vector<std::shared_ptr<Token>> tokens;

    SECTION("single Assign: missing operator") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single Assign: missing variable") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single Assign: missing expr") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single Assign: missing semicolon") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("single Assign factor_int") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(SourceParser(tokens).parse());

        auto parser = SourceParser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(!programNode->procedureList[0]->stmtListNode->stmtList.empty());

        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
        CHECK(stmtNode->stmtIndex == 1);
        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);

        AssignNode* assignNode;
        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
        CHECK(assignNode->varName == "read");

        REQUIRE(assignNode->exprVariables.empty());
        REQUIRE(assignNode->exprConstants.size() == 1);
        REQUIRE(assignNode->exprConstants.find(1) != assignNode->exprConstants.end());
    }

    SECTION("single Assign factor_var") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(SourceParser(tokens).parse());

        auto parser = SourceParser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(!programNode->procedureList[0]->stmtListNode->stmtList.empty());

        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
        CHECK(stmtNode->stmtIndex == 1);
        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);

        AssignNode* assignNode;
        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
        CHECK(assignNode->varName == "x");

        REQUIRE(assignNode->exprConstants.empty());
        REQUIRE(!assignNode->exprVariables.empty());
        REQUIRE(assignNode->exprVariables.find("y") != assignNode->exprVariables.end());
    }

    SECTION("double Assign same Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(SourceParser(tokens).parse());

        auto parser = SourceParser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 2);

        SECTION("first Assign") {
        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
        CHECK(stmtNode->stmtIndex == 1);
        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);

        AssignNode *assignNode;
        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode *>(stmtNode.get()));
        CHECK(assignNode->varName == "x");

        REQUIRE(!assignNode->exprConstants.empty());
        REQUIRE(assignNode->exprVariables.empty());
        REQUIRE(assignNode->exprConstants.find(1) != assignNode->exprConstants.end());
    }


        SECTION("second Assign") {
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
            CHECK(stmtNode->stmtIndex == 2);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);

            AssignNode* assignNode;
            REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
            CHECK(assignNode->varName == "y");

            REQUIRE(assignNode->exprConstants.empty());
            REQUIRE(!assignNode->exprVariables.empty());
            REQUIRE(assignNode->exprVariables.find("x") != assignNode->exprVariables.end());
        }
    }

    SECTION("double Assign different Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(SourceParser(tokens).parse());

        auto parser = SourceParser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 2);

        SECTION("first Procedure") {
            REQUIRE(!programNode->procedureList[0]->stmtListNode->stmtList.empty());
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 1);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);

            AssignNode* assignNode;
            REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
            CHECK(assignNode->varName == "x");

            REQUIRE(assignNode->exprVariables.empty());
            REQUIRE(assignNode->exprConstants.find(1) != assignNode->exprConstants.end());
        }

        SECTION("second Procedure") {
            REQUIRE(!programNode->procedureList[1]->stmtListNode->stmtList.empty());
            std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[1]->stmtListNode->stmtList[0];
            CHECK(stmtNode->stmtIndex == 2);
            REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);

            AssignNode* assignNode;
            REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
            CHECK(assignNode->varName == "y");

            REQUIRE(assignNode->exprConstants.empty());
            REQUIRE(assignNode->exprVariables.find("x") != assignNode->exprVariables.end());
        }
    }
}
