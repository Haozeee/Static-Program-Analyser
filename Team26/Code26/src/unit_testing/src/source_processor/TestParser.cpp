#include "catch.hpp"
#include "source_processor/parser/Parser.h"

TEST_CASE("Parser parse empty") {
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    std::shared_ptr<ProgramNode> programNode;

    REQUIRE_NOTHROW(programNode = Parser(tokens).parse());
    CHECK(programNode->procedureList.size() == 0);
}

TEST_CASE("Parser parse procedure") {
    // one procedure: positive test case
    std::vector<std::shared_ptr<Token>> tokens;
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    std::shared_ptr<ProgramNode> programNode;
    REQUIRE_NOTHROW(programNode = Parser(tokens).parse());

    CHECK(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList.size() == 0);

    tokens.clear();

    // two procedures: positive test case
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
    tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
    programNode = Parser(tokens).parse();

    REQUIRE(programNode->procedureList.size() == 2);
    CHECK(programNode->procedureList[0]->procedureName == "proc1");
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList.size() == 0);
    CHECK(programNode->procedureList[1]->procedureName == "proc2");
    CHECK(programNode->procedureList[1]->stmtListNode->stmtList.size() == 0);
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
    REQUIRE_NOTHROW(programNode = Parser(tokens).parse());

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
    REQUIRE_NOTHROW(programNode = Parser(tokens).parse());

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
    REQUIRE_NOTHROW(programNode = Parser(tokens).parse());

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
    REQUIRE_NOTHROW(programNode = Parser(tokens).parse());

    REQUIRE(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtIndex == 1);
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtType == StmtType::STMT_ASSIGN);

    AssignNode* assignNode;
    REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(programNode->procedureList[0]->stmtListNode->stmtList[0].get()));
    CHECK(assignNode->varName == "x");
    CHECK_FALSE(assignNode->exprNode->optionalParams.has_value());
    CHECK_FALSE(assignNode->exprNode->term->optionalParams.has_value());
    // TODO(oviya): check redundancy of Factor
    Factor factor = *(assignNode->exprNode->term->factor);
    REQUIRE(std::holds_alternative<std::string>(factor));
    REQUIRE_FALSE(std::holds_alternative<int>(factor));
    std::string* f;
    REQUIRE_NOTHROW(f = std::get_if<std::string>(&factor));
    CHECK(*f == "1");
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
    REQUIRE_NOTHROW(programNode = Parser(tokens).parse());

    REQUIRE(programNode->procedureList.size() == 1);
    CHECK(programNode->procedureList[0]->procedureName == "proc");
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
    CHECK(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtIndex == 1);
    REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList[0]->stmtType == StmtType::STMT_ASSIGN);

    AssignNode* assignNode;
    REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(programNode->procedureList[0]->stmtListNode->stmtList[0].get()));
    CHECK(assignNode->varName == "x");
    CHECK_FALSE(assignNode->exprNode->optionalParams.has_value());
    CHECK_FALSE(assignNode->exprNode->term->optionalParams.has_value());
    // TODO(oviya): check redundancy of Factor
    Factor factor = *(assignNode->exprNode->term->factor);
    REQUIRE(std::holds_alternative<std::string>(factor));
    REQUIRE_FALSE(std::holds_alternative<int>(factor));
    std::string* f;
    REQUIRE_NOTHROW(f = std::get_if<std::string>(&factor));
    CHECK(*f == "1");
}
