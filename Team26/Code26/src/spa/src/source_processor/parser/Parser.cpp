#include "Parser.h"
#include <memory>
#include <string>
#include <utility>

#define INITIAL_STMT_INDEX 0
#define STMTLIST_START "{"
#define STMTLIST_END "}"
#define BRACKETS_START "("
#define BRACKETS_END ")"
#define STMT_END ";"
#define EQUAL_OPERATOR "="
#define MULTIPLY_OPERATOR '*'
#define DIVIDE_OPERATOR '/'
#define MOD_OPERATOR '%'
#define PROCEDURE_KEYWORD "procedure"
#define CALL_KEYWORD "call"
#define PRINT_KEYWORD "print"
#define READ_KEYWORD "read"
#define WHILE_KEYWORD "while"
#define IF_KEYWORD "if"
#define THEN_KEYWORD "then"
#define ELSE_KEYWORD "else"

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens)
    : AbstractParser(tokens), stmtIndex(INITIAL_STMT_INDEX) {}

std::shared_ptr<ProgramNode> Parser::parse() {
    std::vector<std::shared_ptr<ProcedureNode>> procedureList;
    while (!isTypeOf(TokenType::TOKEN_END_OF_FILE)) {
        procedureList.emplace_back(parseProcedure());
    }

    if (procedureList.empty()) {
        // TODO(oviya): Throw exception
    }

    return std::make_shared<ProgramNode>(procedureList);
}

std::shared_ptr<ProcedureNode> Parser::parseProcedure() {
    parseNext(PROCEDURE_KEYWORD);
    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> stmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    return std::make_shared<ProcedureNode>(nameToken->getValue(), stmtListNode);
}

std::shared_ptr<StmtListNode> Parser::parseStmtList() {
    std::vector<std::shared_ptr<StmtNode>> stmtList;

    while (!isValueOf(STMTLIST_END)) {
        if (!isTypeOf(TokenType::TOKEN_NAME)) {
            // TODO(oviya): Throw exception
        }

        std::shared_ptr<StmtNode> stmtNode;
        std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);

        if (nameToken->getValue() == PRINT_KEYWORD) {
            stmtNode = parsePrint();
        } else if (nameToken->getValue() == READ_KEYWORD) {
            stmtNode = parseRead();
        } else if (nameToken->getValue() == CALL_KEYWORD) {
            stmtNode = parseCall();
//        } else if (nameToken->getValue() == WHILE_KEYWORD) {
//            stmtNode = parseWhile();
//        } else if (nameToken->getValue() == IF_KEYWORD) {
//            stmtNode = parseIf();
        } else if (isValueOf(EQUAL_OPERATOR)) {
            stmtNode = parseAssign(nameToken);
        } else {
            // TODO(oviya): Throw exception
        }

        stmtList.emplace_back(stmtNode);
    }

    if (stmtList.empty()) {
        // TODO(oviya): Throw exception
    }

    return std::make_shared<StmtListNode>(stmtList);
}

// std::shared_ptr<WhileNode> Parser::parseWhile() {
//    parseNext(BRACKETS_START);
//    std::string condExprStr = "";
//    while (!isValueOf(BRACKETS_END)) {
//        condExprStr += getToken()->getValue();
//        getNext();
//    }
//    std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(condExprStr);
//    parseNext(BRACKETS_END);
//    parseNext(STMTLIST_START);
//    std::shared_ptr<StmtListNode> stmtListNode = parseStmtList();
//    parseNext(STMTLIST_END);
//    stmtIndex++;
//
//    return std::make_shared<WhileNode>(stmtIndex, condExprNode, stmtListNode);
// }

std::shared_ptr<CondExprNode> Parser::parseCondExprNode(std::string condExpr) {
    if (getNext()->getValue() == BRACKETS_START) {
        // TODO(oviya): implement
    }
    // handle operators
}

std::shared_ptr<ExprNode> Parser::parseExpr(std::string expr) {
    std::shared_ptr<Token> exprToken;

    if (isTypeOf(TokenType::TOKEN_NAME)) {
        exprToken = parseNext(TokenType::TOKEN_NAME);
    } else if (isTypeOf(TokenType::TOKEN_INTEGER)) {
        exprToken = parseNext(TokenType::TOKEN_INTEGER);
    } else {
        // TODO(oviya): throw exception
    }

    // TODO(oviya): proper parsing of ExprNode
    Term* term2;
    ExprNode* expr2;
    Factor factor = 1;
    auto termOptionalParams = std::make_optional(std::pair(TermOperatorType::OPERATOR_MULTIPLY, term2));
    Term term = { factor,  termOptionalParams };
    auto exprOptionalParams = std::make_optional(std::make_pair(ExprOperatorType::OPERATOR_ADD, expr2));
    return std::make_shared<ExprNode>(term, exprOptionalParams);
}

std::shared_ptr<Term> Parser::parseTerm(std::string term) {
    std::string firstSubStr = "";
    std::string secondSubStr = "";
    std::optional<TermOperatorType> opType;
    int bracketCount = 0;

    std::string* currStr = &firstSubStr;

    for (char& c : term) {
        if (c == MULTIPLY_OPERATOR) {
            if (firstSubStr.empty()) {
                // TODO(oviya): throw error
            }

            opType = TermOperatorType::OPERATOR_MULTIPLY;
            currStr = &secondSubStr;
        } else if (c == DIVIDE_OPERATOR) {
            if (firstSubStr.empty()) {
                // TODO(oviya): throw error
            }

            opType = TermOperatorType::OPERATOR_DIVIDE;
            currStr = &secondSubStr;
        } else if (c == MOD_OPERATOR) {
            if (firstSubStr.empty()) {
                // TODO(oviya): throw error
            }
            opType = TermOperatorType::OPERATOR_MOD;
            currStr = &secondSubStr;
        }
        if (opType.has_value()) {
            // TODO(oviya): implement
        }
    }
}

std::shared_ptr<AssignNode> Parser::parseAssign(std::shared_ptr<Token> nameToken) {
    parseNext(EQUAL_OPERATOR);
    std::string expr = "";
    ExprNode exprNode = *parseExpr(expr);
    parseNext(STMT_END);
    stmtIndex++;

    return std::make_shared<AssignNode>(stmtIndex, nameToken->getValue(), exprNode);
}

std::shared_ptr<ReadNode> Parser::parseRead() {
    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    parseNext(STMT_END);
    stmtIndex++;

    return std::make_shared<ReadNode>(stmtIndex, nameToken->getValue());
}

std::shared_ptr<PrintNode> Parser::parsePrint() {
    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    parseNext(STMT_END);
    stmtIndex++;

    return std::make_shared<PrintNode>(stmtIndex, nameToken->getValue());
}

std::shared_ptr<CallNode> Parser::parseCall() {
    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    parseNext(STMT_END);
    stmtIndex++;

    return std::make_shared<CallNode>(stmtIndex, nameToken->getValue());
}
