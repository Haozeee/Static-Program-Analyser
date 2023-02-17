#include "catch.hpp"
#include "source_processor/parser/Parser.h"
#include "source_processor/node/statement_node/VariableNameNode.h"
#include <iostream>
//TEST_CASE("Parser parseProgram") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("empty Source") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single stmt Source") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("stmt outside Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//}
//
//TEST_CASE("Parser Procedure") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("empty Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single procedure: missing keyword") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single procedure: missing procedure name") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single procedure: missing start braces") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single procedure: missing end braces") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        CHECK(programNode->procedureList[0]->procedureName == "proc");
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
//
//        std::vector<std::shared_ptr<StmtNode>> stmtList =
//            programNode->procedureList[0]->stmtListNode->stmtList;
//        std::shared_ptr<StmtNode> stmtNode = stmtList.at(0);
//        CHECK(stmtList.at(0)->stmtIndex == 1);
//        REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_READ);
//    }
//
//    SECTION("double procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 2);
//
//        SECTION("first procedure") {
//            CHECK(programNode->procedureList[0]->procedureName == "proc1");
//            REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() == 1);
//
//            std::vector<std::shared_ptr<StmtNode>> stmtList =
//                programNode->procedureList[0]->stmtListNode->stmtList;
//            std::shared_ptr<StmtNode> stmtNode = stmtList.at(0);
//            CHECK(stmtList.at(0)->stmtIndex == 1);
//            REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_READ);
//        }
//
//        SECTION("second procedure") {
//            CHECK(programNode->procedureList[1]->procedureName == "proc2");
//            REQUIRE(programNode->procedureList[1]->stmtListNode->stmtList.size() == 1);
//
//            std::vector<std::shared_ptr<StmtNode>> stmtList =
//                programNode->procedureList[1]->stmtListNode->stmtList;
//            std::shared_ptr<StmtNode> stmtNode = stmtList.at(0);
//            CHECK(stmtList.at(0)->stmtIndex == 2);
//            REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_PRINT);
//        }
//    }
//}
//
//TEST_CASE("Parser Read") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("single Read: missing keyword") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Read: missing variable name") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Read: missing semicolon") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Read") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);
//
//        ReadNode* readNode;
//        REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get())); 
//        CHECK(readNode->varName == "xyz");
//    }
//
//    SECTION("double Read same Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 2);
//
//        SECTION("first Read") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);
//
//            ReadNode* readNode;
//            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
//            CHECK(readNode->varName == "xyz");
//        }
//
//        SECTION("second Read") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);
//
//            ReadNode* readNode;
//            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
//            CHECK(readNode->varName == "abc");
//        }
//    }
//
//    SECTION("double Read different Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 2);
//
//        SECTION("first Procedure") {
//            REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);
//
//            ReadNode* readNode;
//            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
//            CHECK(readNode->varName == "xyz");
//        }
//
//        SECTION("second Procedure") {
//            REQUIRE(programNode->procedureList[1]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[1]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_READ);
//
//            ReadNode* readNode;
//            REQUIRE_NOTHROW(readNode = dynamic_cast<ReadNode*>(stmtNode.get()));
//            CHECK(readNode->varName == "abc");
//        }
//    }
//}
//
//TEST_CASE("Parser Print") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("single Print: missing keyword") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Print: missing variable name") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Print: missing semicolon") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Print") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_PRINT);
//
//        PrintNode* printNode;
//        REQUIRE_NOTHROW(printNode = dynamic_cast<PrintNode*>(stmtNode.get()));
//        CHECK(printNode->varName == "xyz");
//    }
//
//    SECTION("double Print same Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 2);
//
//        SECTION("first Print") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_PRINT);
//
//            PrintNode* printNode;
//            REQUIRE_NOTHROW(printNode = dynamic_cast<PrintNode*>(stmtNode.get()));
//            CHECK(printNode->varName == "xyz");
//        }
//
//        SECTION("second Print") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_PRINT);
//
//            PrintNode* printNode;
//            REQUIRE_NOTHROW(printNode = dynamic_cast<PrintNode*>(stmtNode.get()));
//            CHECK(printNode->varName == "abc");
//        }
//    }
//
//    SECTION("double Print different Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 2);
//
//        SECTION("first Procedure") {
//            REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_PRINT);
//
//            PrintNode* printNode;
//            REQUIRE_NOTHROW(printNode = dynamic_cast<PrintNode*>(stmtNode.get()));
//            CHECK(printNode->varName == "xyz");
//        }
//
//        SECTION("second Procedure") {
//            REQUIRE(programNode->procedureList[1]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[1]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_PRINT);
//
//            PrintNode* printNode;
//            REQUIRE_NOTHROW(printNode = dynamic_cast<PrintNode*>(stmtNode.get()));
//            CHECK(printNode->varName == "abc");
//        }
//    }
//}
//
//TEST_CASE("Parser Call") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("single Call: missing keyword") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Call: missing variable name") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Call: missing semicolon") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    // TODO(oviya): add call procedure name verification in upcoming milestone.
//
//    SECTION("single Call") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);
//
//        CallNode* callNode;
//        REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
//        CHECK(callNode->processName == "xyz");
//    }
//
//    SECTION("double Call same Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 2);
//
//        SECTION("first Call") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);
//
//            CallNode* callNode;
//            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
//            CHECK(callNode->processName == "xyz");
//        }
//
//        SECTION("second Call") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);
//
//            CallNode* callNode;
//            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
//            CHECK(callNode->processName == "abc");
//        }
//    }
//
//    SECTION("double Call different Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "xyz"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "call"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "abc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 2);
//
//        SECTION("first Procedure") {
//            REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);
//
//            CallNode* callNode;
//            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
//            CHECK(callNode->processName == "xyz");
//        }
//
//        SECTION("second Procedure") {
//            REQUIRE(programNode->procedureList[1]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[1]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_CALL);
//
//            CallNode* callNode;
//            REQUIRE_NOTHROW(callNode = dynamic_cast<CallNode*>(stmtNode.get()));
//            CHECK(callNode->processName == "abc");
//        }
//    }
//}
//
//TEST_CASE("Parser Assign") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("single Assign: missing operator") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Assign: missing variable") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Assign: missing expr") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Assign: missing semicolon") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single Assign factor_int") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//        CHECK(assignNode->varName == "x");
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(!exprNode->returnNodes().has_value());
//        CHECK(exprNode->getConstant().value() == 1);
//    }
//
//    SECTION("single Assign factor_var") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//        CHECK(assignNode->varName == "x");
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(exprNode->isVariable());
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->returnNodes().has_value());
//        CHECK(exprNode->getVariable().value() == "y");
//    }
//
//
//
//    SECTION("double Assign same Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 2);
//
//        SECTION("first Assign") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//            AssignNode* assignNode;
//            REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//            CHECK(assignNode->varName == "x");
//
//            auto exprNode = assignNode->exprNode;
//            REQUIRE(exprNode->isConstant());
//            REQUIRE(!exprNode->isVariable());
//            REQUIRE(!exprNode->returnNodes().has_value());
//            CHECK(exprNode->getConstant().value() == 1);
//        }
//
//        SECTION("second Assign") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//            AssignNode* assignNode;
//            REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//            CHECK(assignNode->varName == "y");
//
//            auto exprNode = assignNode->exprNode;
//            REQUIRE(exprNode->isVariable());
//            REQUIRE(!exprNode->isConstant());
//            REQUIRE(!exprNode->returnNodes().has_value());
//            CHECK(exprNode->getVariable().value() == "x");
//        }
//    }
//    
//    SECTION("double Assign different Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 2);
//
//        SECTION("first Procedure") {
//            REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//            AssignNode* assignNode;
//            REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//            CHECK(assignNode->varName == "x");
//
//            auto exprNode = assignNode->exprNode;
//            REQUIRE(exprNode->isConstant());
//            REQUIRE(!exprNode->isVariable());
//            REQUIRE(!exprNode->returnNodes().has_value());
//            CHECK(exprNode->getConstant().value() == 1);
//        }
//
//        SECTION("second Procedure") {
//            REQUIRE(programNode->procedureList[1]->stmtListNode->stmtList.size() >= 1);
//            auto stmtNode = programNode->procedureList[1]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 2);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//            AssignNode* assignNode;
//            REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//            CHECK(assignNode->varName == "y");
//
//            auto exprNode = assignNode->exprNode;
//            REQUIRE(exprNode->isVariable());
//            REQUIRE(!exprNode->isConstant());
//            REQUIRE(!exprNode->returnNodes().has_value());
//            CHECK(exprNode->getVariable().value() == "x");
//        }
//    }
//}

//TEST_CASE("Parser ExprNode") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("factor_int") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//    }
//    
//    SECTION("factor_var") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//    }
//    
//    SECTION("(factor_var)") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//    
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//        CHECK(assignNode->varName == "x");
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(exprNode->isVariable());
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->returnNodes().has_value());
//        CHECK(exprNode->getVariable().value() == "y");
//    }
//
//    SECTION("factor */%+- factor") {
//        std::string op = "*/%+-";
//
//        for (char& c : op) {
//            std::string c(1, c);
//            std::string title = std::string("factor ") + c + std::string(" factor");
//            SECTION(title) {
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, c));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//                REQUIRE_NOTHROW(Parser(tokens).parse());
//
//                auto parser = Parser(tokens);
//                parser.parse();
//                std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//                REQUIRE(programNode->procedureList.size() == 1);
//                REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//                auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//                CHECK(stmtNode->stmtIndex == 1);
//                REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//                AssignNode* assignNode;
//                REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//                auto exprNode = assignNode->exprNode;
//                REQUIRE(!exprNode->isConstant());
//                REQUIRE(!exprNode->isVariable());
//                REQUIRE(exprNode->returnNodes().has_value());
//
//                auto nodes = exprNode->returnNodes().value();
//                SECTION("left ExprNode") {
//                    auto child = nodes.first;
//                    REQUIRE(child->isVariable());
//                    REQUIRE(!child->isConstant());
//                    REQUIRE(!child->returnNodes().has_value());
//                    CHECK(child->getVariable().value() == "y");
//                }
//
//                SECTION("right ExprNode") {
//                    auto child = nodes.second;
//                    REQUIRE(child->isConstant());
//                    REQUIRE(!child->isVariable());
//                    REQUIRE(!child->returnNodes().has_value());
//                    CHECK(child->getConstant().value() == 3);
//                }
//
//                tokens.clear();
//            }
//        }
//    }
//
//    SECTION("left associative op pair (.~) (factor . factor) ~ factor") {
//        std::vector<std::string> opPairsLAssociative = { "++", "--", "**", "%%", "//", "*+", "*-", "%+", "%-", "/+", "/-", "+-",
//        "-+", "*/", "*%", "/*", "/%", "%/", "%*" };
//
//        for (std::string& s : opPairsLAssociative) {
//            std::string c1(1, s[0]);
//            std::string c2(1, s[1]);
//            std::string title = std::string("factor ") + c1 + std::string(" factor ") + c2 + std::string(" factor");
//            SECTION(title) {
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, c1));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, c2));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//                REQUIRE_NOTHROW(Parser(tokens).parse());
//
//                auto parser = Parser(tokens);
//                parser.parse();
//                std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//                REQUIRE(programNode->procedureList.size() == 1);
//                REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//                auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//                CHECK(stmtNode->stmtIndex == 1);
//                REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//                AssignNode* assignNode;
//                REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//                auto exprNode = assignNode->exprNode;
//                REQUIRE(!exprNode->isConstant());
//                REQUIRE(!exprNode->isVariable());
//                REQUIRE(exprNode->returnNodes().has_value());
//
//                auto nodes = exprNode->returnNodes().value();
//                auto subNodes = nodes.first->returnNodes();
//
//                SECTION("left subExprNode") {
//                    auto child1 = subNodes.value().first;
//                    REQUIRE(child1->isConstant());
//                    REQUIRE(!child1->isVariable());
//                    REQUIRE(!child1->returnNodes().has_value());
//                    CHECK(child1->getConstant().value() == 3);
//                }
//
//                SECTION("right subExprNode") {
//                    auto child2 = subNodes.value().second;
//                    REQUIRE(child2->isVariable());
//                    REQUIRE(!child2->isConstant());
//                    REQUIRE(!child2->returnNodes().has_value());
//                    CHECK(child2->getVariable().value() == "y");
//                }
//
//                SECTION("right ExprNode") {
//                    auto child = nodes.second;
//                    REQUIRE(child->isVariable());
//                    REQUIRE(!child->isConstant());
//                    REQUIRE(!child->returnNodes().has_value());
//                    CHECK(child->getVariable().value() == "z");
//                }
//
//                tokens.clear();
//            }
//        }
//    }
//
//    SECTION("factor + factor * factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "+"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "*"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//
//    SECTION("factor + factor / factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "+"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "/"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//
//    SECTION("factor + factor % factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "+"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "%"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//
//    SECTION("factor - factor * factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "-"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "*"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//
//    SECTION("factor - factor / factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "-"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "/"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//
//    SECTION("factor - factor % factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "-"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "%"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//
//    SECTION("(factor + factor) * factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "+"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "*"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//        auto subNodes = nodes.first->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            REQUIRE(child1->isConstant());
//            REQUIRE(!child1->isVariable());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getConstant().value() == 3);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "y");
//        }
//
//        SECTION("right ExprNode") {
//            auto child = nodes.second;
//            REQUIRE(child->isVariable());
//            REQUIRE(!child->isConstant());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getVariable().value() == "z");
//        }
//
//        tokens.clear();
//    }
//
//    SECTION("(factor * factor) + factor") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "*"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "+"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//        auto subNodes = nodes.first->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            REQUIRE(child1->isConstant());
//            REQUIRE(!child1->isVariable());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getConstant().value() == 3);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "y");
//        }
//
//        SECTION("right ExprNode") {
//            auto child = nodes.second;
//            REQUIRE(child->isVariable());
//            REQUIRE(!child->isConstant());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getVariable().value() == "z");
//        }
//
//        tokens.clear();
//    }
//
//    SECTION("factor + (factor * factor)") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "+"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "*"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//
//    SECTION("factor * (factor + factor)") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "="));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "*"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "+"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "z"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        auto exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        auto nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            auto child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            auto child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            auto child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//}

//TEST_CASE("Parser While") {
//    std::vector<std::shared_ptr<Token>> tokens;
//
//    SECTION("single While: missing keyword") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While: missing cond_expr start_bracket") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While: missing cond_expr end_bracket") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While: empty cond_expr") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While: empty cond_expr") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While: incomplete cond_expr") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While: missing start_braces") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While: missing end_braces") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_THROWS(Parser(tokens).parse());
//    }
//
//    SECTION("single While") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
//
//        WhileNode* whileNode;
//        REQUIRE_NOTHROW(whileNode = dynamic_cast<WhileNode*>(stmtNode.get())); 
//        REQUIRE(!whileNode->condExprNode->isUnaryCondExpr());
//        REQUIRE(!whileNode->condExprNode->isBinaryCondExpr());
//        REQUIRE(whileNode->condExprNode->isRelExpr());
//        REQUIRE(whileNode->condExprNode->returnRelExprNodes().has_value());
//        
//        auto relExprNodes = whileNode->condExprNode->returnRelExprNodes().value();
//        auto exprNode1 = relExprNodes.first;
//        REQUIRE(exprNode1->isVariable());
//        REQUIRE(!exprNode1->isConstant());
//        REQUIRE(!exprNode1->returnNodes().has_value());
//        CHECK(exprNode1->getVariable().value() == "num1");
//        auto exprNode2 = relExprNodes.second;
//        REQUIRE(exprNode2->isConstant());
//        REQUIRE(!exprNode2->isVariable());
//        REQUIRE(!exprNode2->returnNodes().has_value());
//        CHECK(exprNode2->getConstant().value() == 0);
//
//        auto stmtList = whileNode->stmtListNode->stmtList;
//        REQUIRE(stmtList.size() >= 1);
//        CHECK(stmtList.at(0)->stmtType == StmtType::STMT_READ);
//        CHECK(stmtList.at(0)->stmtIndex == 2);
//    }
//
//    SECTION("sequential While same Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 2);
//
//        SECTION("first While") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//            CHECK(stmtNode->stmtIndex == 1);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
//
//            WhileNode* whileNode;
//            REQUIRE_NOTHROW(whileNode = dynamic_cast<WhileNode*>(stmtNode.get()));
//            REQUIRE(!whileNode->condExprNode->isUnaryCondExpr());
//            REQUIRE(!whileNode->condExprNode->isBinaryCondExpr());
//            REQUIRE(whileNode->condExprNode->isRelExpr());
//            REQUIRE(whileNode->condExprNode->returnRelExprNodes().has_value());
//
//            auto relExprNodes = whileNode->condExprNode->returnRelExprNodes().value();
//            auto exprNode1 = relExprNodes.first;
//            REQUIRE(exprNode1->isVariable());
//            REQUIRE(!exprNode1->isConstant());
//            REQUIRE(!exprNode1->returnNodes().has_value());
//            CHECK(exprNode1->getVariable().value() == "num1");
//            auto exprNode2 = relExprNodes.second;
//            REQUIRE(exprNode2->isConstant());
//            REQUIRE(!exprNode2->isVariable());
//            REQUIRE(!exprNode2->returnNodes().has_value());
//            CHECK(exprNode2->getConstant().value() == 0);
//
//            auto stmtList = whileNode->stmtListNode->stmtList;
//            REQUIRE(stmtList.size() >= 1);
//            CHECK(stmtList.at(0)->stmtType == StmtType::STMT_READ);
//            CHECK(stmtList.at(0)->stmtIndex == 2);
//        }
//
//        SECTION("second While") {
//            auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[1];
//            CHECK(stmtNode->stmtIndex == 3);
//            REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
//
//            WhileNode* whileNode;
//            REQUIRE_NOTHROW(whileNode = dynamic_cast<WhileNode*>(stmtNode.get()));
//            REQUIRE(!whileNode->condExprNode->isUnaryCondExpr());
//            REQUIRE(!whileNode->condExprNode->isBinaryCondExpr());
//            REQUIRE(whileNode->condExprNode->isRelExpr());
//            REQUIRE(whileNode->condExprNode->returnRelExprNodes().has_value());
//
//            auto relExprNodes = whileNode->condExprNode->returnRelExprNodes().value();
//            auto exprNode1 = relExprNodes.first;
//            REQUIRE(exprNode1->isVariable());
//            REQUIRE(!exprNode1->isConstant());
//            REQUIRE(!exprNode1->returnNodes().has_value());
//            CHECK(exprNode1->getVariable().value() == "num2");
//            auto exprNode2 = relExprNodes.second;
//            REQUIRE(exprNode2->isConstant());
//            REQUIRE(!exprNode2->isVariable());
//            REQUIRE(!exprNode2->returnNodes().has_value());
//            CHECK(exprNode2->getConstant().value() == 1);
//
//            auto stmtList = whileNode->stmtListNode->stmtList;
//            REQUIRE(stmtList.size() >= 1);
//            CHECK(stmtList.at(0)->stmtType == StmtType::STMT_READ);
//            CHECK(stmtList.at(0)->stmtIndex == 4);
//        }
//    }
//
//    SECTION("nested While same Procedure") {
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
//        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
//        REQUIRE_NOTHROW(Parser(tokens).parse());
//
//        auto parser = Parser(tokens);
//        parser.parse();
//        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();
//
//        REQUIRE(programNode->procedureList.size() == 1);
//        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);
//
//        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
//
//        WhileNode* whileNode;
//        REQUIRE_NOTHROW(whileNode = dynamic_cast<WhileNode*>(stmtNode.get()));
//        REQUIRE(!whileNode->condExprNode->isUnaryCondExpr());
//        REQUIRE(!whileNode->condExprNode->isBinaryCondExpr());
//        REQUIRE(whileNode->condExprNode->isRelExpr());
//        REQUIRE(whileNode->condExprNode->returnRelExprNodes().has_value());
//
//        auto relExprNodes = whileNode->condExprNode->returnRelExprNodes().value();
//        auto exprNode1 = relExprNodes.first;
//        REQUIRE(exprNode1->isVariable());
//        REQUIRE(!exprNode1->isConstant());
//        REQUIRE(!exprNode1->returnNodes().has_value());
//        CHECK(exprNode1->getVariable().value() == "num1");
//        auto exprNode2 = relExprNodes.second;
//        REQUIRE(exprNode2->isConstant());
//        REQUIRE(!exprNode2->isVariable());
//        REQUIRE(!exprNode2->returnNodes().has_value());
//        CHECK(exprNode2->getConstant().value() == 0);
//
//        auto stmtList = whileNode->stmtListNode->stmtList;
//        REQUIRE(stmtList.size() >= 1);
//        CHECK(stmtList.at(0)->stmtIndex == 2);
//        REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_WHILE);
//
//        REQUIRE_NOTHROW(whileNode = dynamic_cast<WhileNode*>(stmtList.at(0).get()));
//        REQUIRE(!whileNode->condExprNode->isUnaryCondExpr());
//        REQUIRE(!whileNode->condExprNode->isBinaryCondExpr());
//        REQUIRE(whileNode->condExprNode->isRelExpr());
//        REQUIRE(whileNode->condExprNode->returnRelExprNodes().has_value());
//
//        relExprNodes = whileNode->condExprNode->returnRelExprNodes().value();
//        exprNode1 = relExprNodes.first;
//        REQUIRE(exprNode1->isVariable());
//        REQUIRE(!exprNode1->isConstant());
//        REQUIRE(!exprNode1->returnNodes().has_value());
//        CHECK(exprNode1->getVariable().value() == "num2");
//        exprNode2 = relExprNodes.second;
//        REQUIRE(exprNode2->isConstant());
//        REQUIRE(!exprNode2->isVariable());
//        REQUIRE(!exprNode2->returnNodes().has_value());
//        CHECK(exprNode2->getConstant().value() == 1);
//
//        stmtList = whileNode->stmtListNode->stmtList;
//        REQUIRE(stmtList.size() >= 1);
//        CHECK(stmtList.at(0)->stmtType == StmtType::STMT_READ);
//        CHECK(stmtList.at(0)->stmtIndex == 3);
//    }
//
//    // TODO(oviya): add unit test for multiple procedures in upcoming sprint.
//}

TEST_CASE("Parser If") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("single If: missing keyword") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num3"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single If: missing start_braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "then"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num3"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single If: missing end_braces") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(Parser(tokens).parse());
    }

    SECTION("single If") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "then"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num3"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);

        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
        CHECK(stmtNode->stmtIndex == 1);
        REQUIRE(stmtNode->stmtType == StmtType::STMT_IF);

        IfNode* ifNode;
        REQUIRE_NOTHROW(ifNode = dynamic_cast<IfNode*>(stmtNode.get()));
        REQUIRE(!ifNode->condExprNode->isUnaryCondExpr());
        REQUIRE(!ifNode->condExprNode->isBinaryCondExpr());
        REQUIRE(ifNode->condExprNode->isRelExpr());
        REQUIRE(ifNode->condExprNode->returnRelExprNodes().has_value());

        auto relExprNodes = ifNode->condExprNode->returnRelExprNodes().value();
        auto exprNode1 = relExprNodes.first;
        REQUIRE(exprNode1->isVariable());
        REQUIRE(!exprNode1->isConstant());
        REQUIRE(!exprNode1->returnNodes().has_value());
        CHECK(exprNode1->getVariable().value() == "num1");
        auto exprNode2 = relExprNodes.second;
        REQUIRE(exprNode2->isConstant());
        REQUIRE(!exprNode2->isVariable());
        REQUIRE(!exprNode2->returnNodes().has_value());
        CHECK(exprNode2->getConstant().value() == 0);

        auto stmtList = ifNode->thenStmtListNode->stmtList;
        REQUIRE(stmtList.size() >= 1);
        CHECK(stmtList.at(0)->stmtType == StmtType::STMT_READ);
        CHECK(stmtList.at(0)->stmtIndex == 2);

        stmtList = ifNode->elseStmtListNode->stmtList;
        REQUIRE(stmtList.size() >= 1);
        CHECK(stmtList.at(0)->stmtType == StmtType::STMT_PRINT);
        CHECK(stmtList.at(0)->stmtIndex == 3);
    }

    SECTION("nested If same Procedure") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "then"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "if"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ">"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "then"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num1"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "else"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "num2"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_NOTHROW(Parser(tokens).parse());

        auto parser = Parser(tokens);
        parser.parse();
        std::shared_ptr<ProgramNode> programNode = parser.getProgramNode();

        REQUIRE(programNode->procedureList.size() == 1);
        REQUIRE(programNode->procedureList[0]->stmtListNode->stmtList.size() >= 1);

        auto stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
        CHECK(stmtNode->stmtIndex == 1);
        REQUIRE(stmtNode->stmtType == StmtType::STMT_IF);

        IfNode* ifNode;
        REQUIRE_NOTHROW(ifNode = dynamic_cast<IfNode*>(stmtNode.get()));
        REQUIRE(!ifNode->condExprNode->isUnaryCondExpr());
        REQUIRE(!ifNode->condExprNode->isBinaryCondExpr());
        REQUIRE(ifNode->condExprNode->isRelExpr());
        REQUIRE(ifNode->condExprNode->returnRelExprNodes().has_value());

        auto relExprNodes = ifNode->condExprNode->returnRelExprNodes().value();
        auto exprNode1 = relExprNodes.first;
        REQUIRE(exprNode1->isVariable());
        REQUIRE(!exprNode1->isConstant());
        REQUIRE(!exprNode1->returnNodes().has_value());
        CHECK(exprNode1->getVariable().value() == "num1");
        auto exprNode2 = relExprNodes.second;
        REQUIRE(exprNode2->isConstant());
        REQUIRE(!exprNode2->isVariable());
        REQUIRE(!exprNode2->returnNodes().has_value());
        CHECK(exprNode2->getConstant().value() == 0);

        auto stmtList = ifNode->thenStmtListNode->stmtList;
        REQUIRE(stmtList.size() >= 1);
        CHECK(stmtList.at(0)->stmtIndex == 2);
        REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_READ);

        stmtList = ifNode->elseStmtListNode->stmtList;
        REQUIRE(stmtList.size() >= 1);
        CHECK(stmtList.at(0)->stmtIndex == 3);
        REQUIRE(stmtList.at(0)->stmtType == StmtType::STMT_IF);

        REQUIRE_NOTHROW(ifNode = dynamic_cast<IfNode*>(stmtList.at(0).get()));
        REQUIRE(!ifNode->condExprNode->isUnaryCondExpr());
        REQUIRE(!ifNode->condExprNode->isBinaryCondExpr());
        REQUIRE(ifNode->condExprNode->isRelExpr());
        REQUIRE(ifNode->condExprNode->returnRelExprNodes().has_value());

        relExprNodes = ifNode->condExprNode->returnRelExprNodes().value();
        exprNode1 = relExprNodes.first;
        REQUIRE(exprNode1->isVariable());
        REQUIRE(!exprNode1->isConstant());
        REQUIRE(!exprNode1->returnNodes().has_value());
        CHECK(exprNode1->getVariable().value() == "num2");
        exprNode2 = relExprNodes.second;
        REQUIRE(exprNode2->isConstant());
        REQUIRE(!exprNode2->isVariable());
        REQUIRE(!exprNode2->returnNodes().has_value());
        CHECK(exprNode2->getConstant().value() == 1);

        stmtList = ifNode->thenStmtListNode->stmtList;
        REQUIRE(stmtList.size() >= 1);
        CHECK(stmtList.at(0)->stmtType == StmtType::STMT_READ);
        CHECK(stmtList.at(0)->stmtIndex == 4);

        stmtList = ifNode->elseStmtListNode->stmtList;
        REQUIRE(stmtList.size() >= 1);
        CHECK(stmtList.at(0)->stmtType == StmtType::STMT_PRINT);
        CHECK(stmtList.at(0)->stmtIndex == 5);

    }

    // TODO(oviya): add unit test for multiple procedures in upcoming sprint.
}
