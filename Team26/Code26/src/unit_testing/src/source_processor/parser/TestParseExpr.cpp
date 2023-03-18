#include "catch.hpp"
#include "TestSourceParserUtil.h"
#include "source_processor/parser/Parser.h"


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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//        CHECK(assignNode->varName == "x");
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(exprNode->isVariable());
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->returnNodes().has_value());
//        CHECK(exprNode->getVariable().value() == "y");
//    }
//
//    SECTION("factor */%+- factor") {
//        std::string op = "*/%+-";
//
//        for (char& a : op) {
//            std::string c(1, a);
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
//                std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//                CHECK(stmtNode->stmtIndex == 1);
//                REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//                AssignNode* assignNode;
//                REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//                std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//                REQUIRE(!exprNode->isConstant());
//                REQUIRE(!exprNode->isVariable());
//                REQUIRE(exprNode->returnNodes().has_value());
//
//                std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//                    = exprNode->returnNodes().value();
//                SECTION("left ExprNode") {
//                    std::shared_ptr<ExprNode> child = nodes.first;
//                    REQUIRE(child->isVariable());
//                    REQUIRE(!child->isConstant());
//                    REQUIRE(!child->returnNodes().has_value());
//                    CHECK(child->getVariable().value() == "y");
//                }
//
//                SECTION("right ExprNode") {
//                    std::shared_ptr<ExprNode> child = nodes.second;
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
//                std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//                CHECK(stmtNode->stmtIndex == 1);
//                REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//                AssignNode* assignNode;
//                REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//                std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//                REQUIRE(!exprNode->isConstant());
//                REQUIRE(!exprNode->isVariable());
//                REQUIRE(exprNode->returnNodes().has_value());
//
//                std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes = exprNode->returnNodes().value();
//                auto subNodes = nodes.first->returnNodes();
//
//                SECTION("left subExprNode") {
//                    std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//                    REQUIRE(child1->isConstant());
//                    REQUIRE(!child1->isVariable());
//                    REQUIRE(!child1->returnNodes().has_value());
//                    CHECK(child1->getConstant().value() == 3);
//                }
//
//                SECTION("right subExprNode") {
//                    std::shared_ptr<ExprNode> child2 = subNodes.value().second;
//                    REQUIRE(child2->isVariable());
//                    REQUIRE(!child2->isConstant());
//                    REQUIRE(!child2->returnNodes().has_value());
//                    CHECK(child2->getVariable().value() == "y");
//                }
//
//                SECTION("right ExprNode") {
//                    std::shared_ptr<ExprNode> child = nodes.second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//            = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//            = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//            = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//            = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//            = exprNode->returnNodes().value();
//        auto subNodes = nodes.first->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            REQUIRE(child1->isConstant());
//            REQUIRE(!child1->isVariable());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getConstant().value() == 3);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "y");
//        }
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//            = exprNode->returnNodes().value();
//        auto subNodes = nodes.first->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            REQUIRE(child1->isConstant());
//            REQUIRE(!child1->isVariable());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getConstant().value() == 3);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "y");
//        }
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes
//            = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
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
//        std::shared_ptr<StmtNode> stmtNode = programNode->procedureList[0]->stmtListNode->stmtList[0];
//        CHECK(stmtNode->stmtIndex == 1);
//        REQUIRE(stmtNode->stmtType == StmtType::STMT_ASSIGN);
//
//        AssignNode* assignNode;
//        REQUIRE_NOTHROW(assignNode = dynamic_cast<AssignNode*>(stmtNode.get()));
//
//        std::shared_ptr<ExprNode> exprNode = assignNode->exprNode;
//        REQUIRE(!exprNode->isConstant());
//        REQUIRE(!exprNode->isVariable());
//        REQUIRE(exprNode->returnNodes().has_value());
//
//        std::pair<std::shared_ptr<ExprNode>, std::shared_ptr<ExprNode>> nodes = exprNode->returnNodes().value();
//
//        SECTION("right ExprNode") {
//            std::shared_ptr<ExprNode> child = nodes.first;
//            REQUIRE(child->isConstant());
//            REQUIRE(!child->isVariable());
//            REQUIRE(!child->returnNodes().has_value());
//            CHECK(child->getConstant().value() == 3);
//        }
//
//        auto subNodes = nodes.second->returnNodes();
//
//        SECTION("left subExprNode") {
//            std::shared_ptr<ExprNode> child1 = subNodes.value().first;
//            CHECK(subNodes.has_value());
//            REQUIRE(child1->isVariable());
//            REQUIRE(!child1->isConstant());
//            REQUIRE(!child1->returnNodes().has_value());
//            CHECK(child1->getVariable().value() == "y");
//            CHECK(1 == 1);
//        }
//
//        SECTION("right subExprNode") {
//            std::shared_ptr<ExprNode> child2 = subNodes.value().second;
//            REQUIRE(child2->isVariable());
//            REQUIRE(!child2->isConstant());
//            REQUIRE(!child2->returnNodes().has_value());
//            CHECK(child2->getVariable().value() == "z");
//        }
//    }
//}
