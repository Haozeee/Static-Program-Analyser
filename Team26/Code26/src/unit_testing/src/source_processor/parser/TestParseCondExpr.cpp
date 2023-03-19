#include "catch.hpp"
#include "TestSourceParserUtil.h"
#include "source_processor/parser/SourceParser.h"

TEST_CASE("Parser CondExpr") {
    std::vector<std::shared_ptr<Token>> tokens;

    SECTION("invalid cond_expr") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "=="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "4"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_END_OF_FILE, ""));
        REQUIRE_THROWS(SourceParser(tokens).parse());
    }

    SECTION("rel_expr") {
        std::vector<std::string> relOps = { ">", ">=", "<", "<=", "==", "!=" };
        std::vector<std::string> exprTermOps = { "+", "-", "*", "/", "%" };

        std::vector<std::tuple<int, int, int>> indices = TestSourceParserUtil::generatePermutations(relOps.size(),
            exprTermOps.size(), exprTermOps.size());

        for (auto& tuple : indices) {
            std::string relOp = relOps.at(std::get<0>(tuple));
            std::string title = std::string("factor ") + relOp + std::string(" factor");
            SECTION(title) {
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, relOp));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
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
                REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);


            }


            std::string exprTermOp1 = exprTermOps.at(std::get<1>(tuple));
            std::string exprTermOp2 = exprTermOps.at(std::get<2>(tuple));
            title = std::string("factor ") + exprTermOp1 + std::string(" factor ") + relOp
                + std::string(" factor ") + exprTermOp2 + std::string (" factor");
            SECTION(title) {
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, exprTermOp1));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, relOp));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, exprTermOp2));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "4"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
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
                REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
            }

            title = std::string("(factor ") + exprTermOp1 + std::string(" factor) ") + relOp
                + std::string(" (factor ") + exprTermOp2 + std::string(" factor)");
            SECTION(title) {
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, exprTermOp1));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, relOp));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, exprTermOp2));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "4"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
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
                REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
            }
        }
    }

    SECTION("unary_cond_expr") {
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "!"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "=="));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "0"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
        tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
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
        REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
    }

    SECTION("binary_cond_expr") {
        std::vector<std::string> binaryOps = { "&&", "||" };
        std::vector<std::string> relOps = { ">", ">=", "<", "<=", "==", "!=" };
        auto indices = TestSourceParserUtil::generatePermutations(binaryOps.size(), relOps.size(),
            relOps.size());
        std::unordered_set<std::string> collect;
        for (auto& tuple: indices) {
            std::string binaryOp = binaryOps.at(std::get<0>(tuple));
            std::string relOp1 = relOps.at(std::get<1>(tuple));
            std::string relOp2 = relOps.at(std::get<2>(tuple));
            std::string title = std::string("(factor ") + relOp1 + std::string(" factor)") + binaryOp
                + std::string("(factor ") + relOp2 + std::string(" factor)");
            SECTION(title) {
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "procedure"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "proc"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "while"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "x"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, relOp1));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "print"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, binaryOp));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "("));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "3"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, relOp2));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_INTEGER, "4"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ")"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "{"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "read"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_NAME, "y"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, ";"));
                tokens.push_back(std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, "}"));
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
                REQUIRE(stmtNode->stmtType == StmtType::STMT_WHILE);
            }
        }
    }
}
