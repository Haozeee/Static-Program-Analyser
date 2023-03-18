#include "Parser.h"

#include <utility>
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
#define NOT_OPERATOR "!"
#define PROCEDURE_KEYWORD "procedure"
#define CALL_KEYWORD "call"
#define PRINT_KEYWORD "print"
#define READ_KEYWORD "read"
#define WHILE_KEYWORD "while"
#define IF_KEYWORD "if"
#define THEN_KEYWORD "then"
#define ELSE_KEYWORD "else"

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens)
    : AbstractParser(std::move(tokens)), stmtIndex(INITIAL_STMT_INDEX) {}

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
    index = index - 1;
    std::queue<std::shared_ptr<Token>> postfix;
    std::stack<std::shared_ptr<Token>> opStack;

    int numOfBrackets = 0;
    while (!isTypeOf(TokenType::TOKEN_END_OF_FILE)) {
        if (getToken()->isIntegerOrNameToken()) {
            postfix.push(getToken());
        } else if (isValueOf(BRACKETS_START)) {
            opStack.push(getToken());
            numOfBrackets++;
        } else if (isValueOf(BRACKETS_END)) {
            numOfBrackets--;
            buildNestExpr(opStack, postfix);
            if (numOfBrackets == 0) break;
        } else {
            buildPostFixHelper(opStack, postfix);
        }
        getNext();
    }

    if (numOfBrackets != 0) {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }

    while (!opStack.empty()) {
        postfix.push(opStack.top());
        opStack.pop();
    }

    return buildConditionalExpr(postfix);
}

void Parser::buildPostFixHelper(std::stack<std::shared_ptr<Token>>& opStack,
                                std::queue<std::shared_ptr<Token>>& postfix) {
    while (!opStack.empty() && isGreaterOrEqualRank(opStack.top()->getValue(), getToken()->getValue())) {
        postfix.push(opStack.top());
        opStack.pop();
    }
    opStack.push(getToken());
}

std::shared_ptr<CondExprNode> Parser::buildConditionalExpr(std::queue<std::shared_ptr<Token>>& postfix) {
    std::stack<HelperNode> result;
    std::shared_ptr<std::unordered_set<std::string>> variables = std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<int>> constants = std::make_shared<std::unordered_set<int>>();

    while (!postfix.empty()) {
        std::shared_ptr<Token> curr = postfix.front();
        postfix.pop();
        if (curr->getType() == TokenType::TOKEN_NAME) {
            variables->insert(curr->getValue());
            result.push(HelperNode::ExprHelper);
        } else if (curr->getType() == TokenType::TOKEN_INTEGER) {
            constants->insert(stoi(curr->getValue()));
            result.push(HelperNode::ExprHelper);
        } else if (isMathOp(curr->getValue())) {
            checkStackSize(result);
            popExprHelper(result);
            continueExprHelper(result);
        } else if (curr->getValue() == NOT_OPERATOR) {
            continueCondExprHelper(result);
        } else if (isCondOp(curr->getValue())) {
            checkStackSize(result);
            popCondExprHelper(result);
            continueCondExprHelper(result);
        } else if (isRelOp(curr->getValue())) {
            checkStackSize(result);
            popExprHelper(result);
            popExprHelper(result);
            result.push(HelperNode::CondExprHelper);
        } else {
            throw SourceParserException(ParserInvalidCondExprExceptionMessage);
        }
    }
    if (result.empty() || result.top() == HelperNode::ExprHelper) /* Empty Expr or Expr Node */ {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
    return std::make_shared<CondExprNode>(*variables, *constants);
}

std::shared_ptr<AssignNode> Parser::parseAssign(const std::shared_ptr<Token>& nameToken) {
    stmtIndex++;
    parseNext(ASSIGN_OPERATOR);

    int currIndex = index;
    while (!isValueOf(STMT_END) && !isTypeOf(TokenType::TOKEN_END_OF_FILE)) {
        getNext();
    }
    int newIndex = index - 1;
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

std::shared_ptr<ProgramNode> Parser::getProgramNode() {
    return this->programRoot;
}

void Parser::popExprHelper(std::stack<HelperNode>& result) {
    if (result.top() == HelperNode::ExprHelper) {
        result.pop();
    } else {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
}

void Parser::continueExprHelper(std::stack<HelperNode>& result) {
    if (result.top() == HelperNode::ExprHelper) {
        return;
    } else {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
}

void Parser::popCondExprHelper(std::stack<HelperNode>& result) {
    if (result.top() == HelperNode::CondExprHelper) {
        result.pop();
    } else {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
}

void Parser::continueCondExprHelper(std::stack<HelperNode>& result) {
    if (result.top() == HelperNode::CondExprHelper) {
        return;
    } else {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
}

void Parser::checkStackSize(std::stack<HelperNode>& result) {
    if (result.size() < 2) {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
}

void Parser::buildNestExpr(std::stack<std::shared_ptr<Token>>& opStack, std::queue<std::shared_ptr<Token>>& postfix) {
    bool isRelExpr = false;
    while (!opStack.empty() && opStack.top()->getValue() != BRACKETS_START) {
        if (isRelOp(opStack.top()->getValue())) {
            isRelExpr = true;
        }
        postfix.push(opStack.top());
        opStack.pop();
    }
    if (!opStack.empty()) {
        opStack.pop();
    } else {
        throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
    if (isRelExpr &&
        !opStack.empty() &&
        opStack.top()->getValue() == BRACKETS_START &&
        !isCondOp(tokens[index+1]->getValue())) {
            throw SourceParserException(ParserInvalidCondExprExceptionMessage);
    }
}

bool Parser::isGreaterOrEqualRank(const std::string& lhs, const std::string& rhs) {
    std::unordered_map<std::string, int> ranking {
            {"&&", 1},
            {"||", 1},
            {"!", 1},
            {">", 2},
            {">=", 2},
            {"<", 2},
            {"<=", 2},
            {"==", 2},
            {"!=", 2},
            {"+", 3},
            {"-", 3},
            {"*", 4},
            {"/", 4},
            {"%", 4}};
    return ranking[lhs] >= ranking[rhs];
}

bool Parser::isMathOp(const std::string& value) {
    std::unordered_set<std::string> mathOp { "+", "-", "*", "/", "%" };
    return mathOp.find(value) != mathOp.end();
}

bool Parser::isCondOp(const std::string& value) {
    std::unordered_set<std::string> condOp {"&&","||"};
    return condOp.find(value) != condOp.end();
}

bool Parser::isRelOp(const std::string& value) {
    std::unordered_set<std::string> relOp { ">", ">=", "<", "<=", "==", "!=" };
    return relOp.find(value) != relOp.end();
}
