#include "Parser.h"
#include "source_processor/exception/SourceException.h"
#include "source_processor/exception/SourceProcessorExceptionMessage.h"
#include "common/parser/ShuntingYardParser.h"

#define INITIAL_STMT_INDEX 0
#define STMTLIST_START "{"
#define STMTLIST_END "}"
#define BRACKETS_START "("
#define BRACKETS_END ")"
#define STMT_END ";"
#define ASSIGN_OPERATOR "="
#define MULTIPLY_OPERATOR "*"
#define DIVIDE_OPERATOR "/"
#define MOD_OPERATOR "%"
#define ADD_OPERATOR "+"
#define SUBTRACT_OPERATOR "-"
#define GT_OPERATOR ">"
#define GTE_OPERATOR ">="
#define LT_OPERATOR "<"
#define LTE_OPERATOR "<="
#define EQ_OPERATOR "=="
#define NEQ_OPERATOR "!="
#define NOT_OPERATOR "!"
#define AND_OPERATOR "&&"
#define OR_OPERATOR "||"
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

void Parser::parse() {
    programRoot = parseProgram();
}

std::shared_ptr<ProgramNode> Parser::parseProgram() {
    std::vector<std::shared_ptr<ProcedureNode>> procedureList;
    while (!isTypeOf(TokenType::TOKEN_END_OF_FILE)) {
        procedureList.emplace_back(parseProcedure());
    }

    if (procedureList.empty()) {
        throw SourceParserException(ParserEmptySourceExceptionMessage);
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
            throw SourceParserException(ParserInvalidStmtStartTokenTypeExceptionMessage);
        }
        std::shared_ptr<StmtNode> stmtNode;
        std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);

        if (isValueOf(ASSIGN_OPERATOR)) {
            stmtNode = parseAssign(nameToken);
        } else if (nameToken->getValue() == PRINT_KEYWORD) {
            stmtNode = parsePrint();
        } else if (nameToken->getValue() == READ_KEYWORD) {
            stmtNode = parseRead();
        } else if (nameToken->getValue() == CALL_KEYWORD) {
            stmtNode = parseCall();
        } else if (nameToken->getValue() == WHILE_KEYWORD) {
            stmtNode = parseWhile();
        } else if (nameToken->getValue() == IF_KEYWORD) {
            stmtNode = parseIf();
        } else {
            throw SourceParserException(ParserInvalidStmtStartTokenUnknownExceptionMessage);
        }

        stmtList.emplace_back(stmtNode);
    }

    if (stmtList.empty()) {
        throw SourceParserException(ParserEmptyStmtListExceptionMessage);
    }

    return std::make_shared<StmtListNode>(stmtList);
}

std::shared_ptr<WhileNode> Parser::parseWhile() {
    int whileStmtIndex = ++stmtIndex;
    parseNext(BRACKETS_START);
    std::shared_ptr<CondExprNode> condExprNode = parseConditional();
    parseNext(BRACKETS_END);

    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> stmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    return std::make_shared<WhileNode>(whileStmtIndex, condExprNode, stmtListNode);
}

std::shared_ptr<IfNode> Parser::parseIf() {
    int ifStmtIndex = ++stmtIndex;
    parseNext(BRACKETS_START);
    std::shared_ptr<CondExprNode> condExprNode = parseConditional();
    parseNext(BRACKETS_END);

    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    if (nameToken->getValue() != THEN_KEYWORD) {
        throw SourceParserException(ParserMissingThenKeywordExceptionMessage);
    }

    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> thenStmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    nameToken = parseNext(TokenType::TOKEN_NAME);
    if (nameToken->getValue() != ELSE_KEYWORD) {
        throw SourceParserException(ParserMissingElseKeywordExceptionMessage);
    }

    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> elseStmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    return std::make_shared<IfNode>(ifStmtIndex, condExprNode, thenStmtListNode, elseStmtListNode);
}

std::shared_ptr<CondExprNode> Parser::parseConditional() {
    int oldIndex = index - 1;
    int numOfBrackets = 1;
    while (!isTypeOf(TokenType::TOKEN_END_OF_FILE)) {
        if (isValueOf(BRACKETS_START)) {
            numOfBrackets++;
        } else if (isValueOf(BRACKETS_END)) {
            numOfBrackets--;
            if (numOfBrackets == 0) {
                break;
            }
        }

        getNext();
    }

    if (numOfBrackets != 0) {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }

    std::string temp;
    for (int i = oldIndex; i <= index; i++) {
        temp += tokens[i]->getValue();
    }



//    return condExprNode;
}

std::shared_ptr<AssignNode> Parser::parseAssign(std::shared_ptr<Token> nameToken) {
    stmtIndex++;
    parseNext(ASSIGN_OPERATOR);

    int currIndex = index;
    while (!isValueOf(STMT_END) && !isTypeOf(TokenType::TOKEN_END_OF_FILE)) {
        getNext();
    }
    int newIndex = index - 1;
//    auto exprNode = parseExprNode(currIndex, newIndex);
    std::string expr;
    for (int i = currIndex; i <= newIndex; i++) {
        expr += tokens[i]->getValue();
    }

    std::shared_ptr<std::unordered_set<std::string>> variables = std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<int>> constants = std::make_shared<std::unordered_set<int>>();

    auto node = ShuntingYardParser::parse(expr, variables, constants);

    index = newIndex + 1;
    parseNext(STMT_END);

    return std::make_shared<AssignNode>(stmtIndex, nameToken->getValue(), node, *variables, *constants);
}

std::shared_ptr<ReadNode> Parser::parseRead() {
    stmtIndex++;
    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    parseNext(STMT_END);
    return std::make_shared<ReadNode>(stmtIndex, nameToken->getValue());
}

std::shared_ptr<PrintNode> Parser::parsePrint() {
    stmtIndex++;
    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    parseNext(STMT_END);

    return std::make_shared<PrintNode>(stmtIndex, nameToken->getValue());
}

std::shared_ptr<CallNode> Parser::parseCall() {
    stmtIndex++;
    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    parseNext(STMT_END);

    return std::make_shared<CallNode>(stmtIndex, nameToken->getValue());
}

std::string Parser::toString(int startIndex, int endIndex) {
    int oldIndex = index;
    index = startIndex;

    std::string result = "";
    while (index <= endIndex) {
        result += getToken()->getValue();
        getNext();
    }

    index = oldIndex;
    return result;
}

std::shared_ptr<ProgramNode> Parser::getProgramNode() {
    return this->programRoot;
}
