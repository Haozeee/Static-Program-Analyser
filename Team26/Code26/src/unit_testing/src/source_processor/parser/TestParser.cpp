#include "catch.hpp"
#include "source_processor/parser/Parser.h"

TEST_CASE("Parser parseProgram") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("empty Source") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };

    SECTION("single stmt Source") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };

    SECTION("stmt outside Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };
}

TEST_CASE("Parser Procedure") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("empty Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };

    SECTION("single procedure: missing keyword") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };

    SECTION("single procedure: missing procedure name") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };

    SECTION("single procedure: missing start braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };

    SECTION("single procedure: missing end braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    };

    SECTION("single procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
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
    };

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
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
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
    };
}

TEST_CASE("Parser parse read") {
    // one read stmt: positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(Parser(tokens).parse());

    auto parser = Parser(tokens);
    parser.parse();
    programNode = parser.getProgramNode();

    REQUIRE(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtIndex == 1);
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtType == StmtType::STMT_READ);

    ReadNode* readNode;
    REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(programNode->procedureList[0]->stmtListNode->stmtList[0].get()));
    CHECK(readNode->varName == "xyz");
}

TEST_CASE("Parser parse print") {
    // one print stmt: positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(Parser(tokens).parse());

    auto parser = Parser(tokens);
    parser.parse();
    programNode = parser.getProgramNode();

    REQUIRE(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtIndex == 1);
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtType == StmtType::STMT_PRINT);

    PrintNode* printNode;
    REQUIRE_NOTHROW(printNode = dynamic_cast<PrintNode*>(programNode->procedureList[0]->stmtListNode->stmtList[0].get()));
    CHECK(printNode->varName == "xyz");
}

TEST_CASE("Parser parse call") {
    // one call stmt: positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(Parser(tokens).parse());

    auto parser = Parser(tokens);
    parser.parse();
    programNode = parser.getProgramNode();

    REQUIRE(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtIndex == 1);
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtType == StmtType::STMT_CALL);

    CallNode* callNode;
    REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(programNode->procedureList[0]->stmtListNode->stmtList[0].get()));
    CHECK(callNode->processName == "xyz");
}

TEST_CASE("Parser parse assign int") {
    // one assign stmt with int: positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(Parser(tokens).parse());

    auto parser = Parser(tokens);
    parser.parse();
    programNode = parser.getProgramNode();

    REQUIRE(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtIndex == 1);
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtType == StmtType::STMT_ASSIGN);

//    AssignNode* assignNode;
//    REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(programNode->procedureList[0]->stmtListNode->stmtList[0].get()));
//    CHECK(assignNode->varName == "x");
//    CHECK_FALSE(assignNode->exprNode->optionalParams.has_value());
//    REQUIRE(std::holds_alternative<std::shared_ptr<Factor>>(assignNode->exprNode->term.first));
}

TEST_CASE("Parser parse assign factor") {
    // one assign stmt with (factor): positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(Parser(tokens).parse());

    auto parser = Parser(tokens);
    parser.parse();
    programNode = parser.getProgramNode();

    REQUIRE(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtIndex == 1);
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtType == StmtType::STMT_ASSIGN);
}


TEST_CASE("Parser parse if") {
    // one if stmt: positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));

    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "then"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));

    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));

    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(Parser(tokens).parse());

    auto parser = Parser(tokens);
    parser.parse();
    programNode = parser.getProgramNode();
}

TEST_CASE("Parser parse while") {
    // one while stmt: positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));

    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));

    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));

    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(Parser(tokens).parse());
}
