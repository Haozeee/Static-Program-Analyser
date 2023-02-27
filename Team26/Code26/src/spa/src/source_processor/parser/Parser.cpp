#include "Parser.h"
#include "source_processor/exception/SourceException.h"
#include "source_processor/exception/SourceProcessorExceptionMessage.h"

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
    int oldIndex = index;
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

    int newIndex = index - 1;
    auto condExprNode = parseCondExprNode(oldIndex, newIndex);
    index = newIndex + 1;
    return condExprNode;
}

std::shared_ptr<CondExprNode> Parser::parseCondExprNode(int startIndex, int endIndex) {
    if (endIndex <= startIndex + 1) {
        throw SourceParserException(ParserInvalidBinaryCondExprFormatExceptionMessage);
    }

    // If cond_expr = rel_expr
    index = endIndex;
    if (!isValueOf(BRACKETS_END)) {
        return std::make_shared<CondExprNode>(parseRelExpr(startIndex, endIndex),
            toString(startIndex, endIndex));
    }

    // If cond_expr = !(cond_expr)
    index = startIndex;
    if (endIndex >= startIndex + 3 && isValueOf(NOT_OPERATOR)) {
        int currIndex = index;
        index++;
        if (getToken()->getValue() == BRACKETS_START) {
            std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(startIndex + 2, endIndex - 1);
            return std::make_shared<CondExprNode>(std::make_tuple(UnaryCondOperatorType::NOT, condExprNode),
                toString(startIndex, endIndex));
        }
        index = currIndex;
    }

    // If cond_expr = rel_expr
    if (!isValueOf(BRACKETS_START)) {
        return std::make_shared<CondExprNode>(parseRelExpr(startIndex, endIndex),
            toString(startIndex, endIndex));
    }

    // If cond_expr = (cond_expr) && (cond_expr) or cond_expr = (cond_expr) || (cond_expr)
    index = startIndex;

    int numOfBrackets = 0;
    while (!isTypeOf(TokenType::TOKEN_END_OF_FILE) && index <= endIndex) {
        if (isBinaryCondOperator() && numOfBrackets == 0) {
            int currIndex = index;
            index--;
            if (!isValueOf(BRACKETS_END)) {
                throw SourceParserException(ParserInvalidBinaryCondExprFormatExceptionMessage);
            }
            index += 2;
            if (!isValueOf(BRACKETS_START)) {
                throw SourceParserException(ParserInvalidBinaryCondExprFormatExceptionMessage);
            }

            index = currIndex;
            auto condExprNode1 = parseCondExprNode(startIndex + 1, currIndex - 2);
            auto condExprNode2 = parseCondExprNode(currIndex + 2, endIndex - 1);
            index = currIndex;

            BinaryCondOperatorType opType = isValueOf(AND_OPERATOR) ? BinaryCondOperatorType::AND
                : BinaryCondOperatorType::OR;
            return std::make_shared<CondExprNode>(std::make_tuple(opType, condExprNode1, condExprNode2),
                toString(startIndex, endIndex));
        } else if (isValueOf(BRACKETS_START)) {
            numOfBrackets++;
        } else if (isValueOf(BRACKETS_END)) {
            numOfBrackets--;
        }
        getNext();
    }

    // If cond_expr = rel_expr
    return std::make_shared<CondExprNode>(parseRelExpr(startIndex, endIndex),
        toString(startIndex, endIndex));
}

bool Parser::isBinaryCondOperator() {
    return isValueOf(AND_OPERATOR) || isValueOf(OR_OPERATOR);
}

std::shared_ptr<RelExpr> Parser::parseRelExpr(int startIndex, int endIndex) {
    if (endIndex <= startIndex + 1) {
        throw SourceParserException(ParserInvalidRelExprExceptionMessage);
    }

    index = startIndex;
    std::optional<RelExprOperatorType> opType = std::nullopt;

    while (getToken()->getType() != TokenType::TOKEN_END_OF_FILE && index <= endIndex) {
        if (isValueOf(GT_OPERATOR)) {
            opType = RelExprOperatorType::GT;
            break;
        } else if (isValueOf(GTE_OPERATOR)) {
            opType = RelExprOperatorType::GTE;
            break;
        } else if (isValueOf(LT_OPERATOR)) {
            opType = RelExprOperatorType::LT;
            break;
        } else if (isValueOf(LTE_OPERATOR)) {
            opType = RelExprOperatorType::LTE;
            break;
        } else if (isValueOf(EQ_OPERATOR)) {
            opType = RelExprOperatorType::EQ;
            break;
        } else if (isValueOf(NEQ_OPERATOR)) {
            opType = RelExprOperatorType::NEQ;
            break;
        }
        getNext();
    }

    if (!opType.has_value()) {
        throw SourceParserException(ParserMissingRelOperatorExceptionMessage);
    }

    int currIndex = index;
    auto exprNode1 = parseExprNode(startIndex, currIndex - 1);
    auto exprNode2 = parseExprNode(currIndex + 1, endIndex);
    return std::make_shared<RelExpr>(std::make_tuple(opType.value(), exprNode1, exprNode2));
}

std::shared_ptr<ExprNode> Parser::parseExprNode(int startIndex, int endIndex) {
    index = endIndex;

    // Parse single name/integer factor
    if (startIndex >= endIndex) {
        return parseFactor(startIndex, endIndex);
    }

    int numOfBrackets = 0;
    bool isPrevTokenStartBracket = false;
    bool isPrevTokenNonBracket = true;
    bool isPrevBracketStartBracket = false;
    bool isPrevBracketEndBracket = false;

    std::vector<int> endBracketStack;

    while (!isTypeOf(TokenType::TOKEN_END_OF_FILE) && index >= startIndex) {
        if (isValueOf(BRACKETS_END)) {
            if (isPrevTokenStartBracket) {
                throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
            }

            isPrevTokenNonBracket = false;
            isPrevTokenStartBracket = false;
            numOfBrackets--;
            isPrevBracketEndBracket = true;
            isPrevBracketStartBracket = false;
            endBracketStack.emplace_back(index);
        } else if (isValueOf(BRACKETS_START)) {
            if (!isPrevTokenNonBracket && !isPrevTokenStartBracket) {
                throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
            }

            isPrevTokenNonBracket = false;
            isPrevTokenStartBracket = true;
            numOfBrackets++;

            if (endBracketStack.at(0) == endIndex && endBracketStack.size() == 1
                && index == startIndex && numOfBrackets == 0) {
                auto s = parseExprNode(startIndex + 1, endIndex - 1);
                return s;
            }

            if (endBracketStack.empty()) {
                throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
            }

            isPrevBracketEndBracket = false;
            isPrevBracketStartBracket = true;
            endBracketStack.pop_back();
        } else if (isExprOperator() && numOfBrackets == 0) {
            int currIndex = index;
            auto exprNode1 = parseExprNode(startIndex, currIndex - 1);
            auto exprNode2 = parseExprNode(currIndex + 1, endIndex);
            index = currIndex;

            return std::make_shared<ExprNode>(std::make_shared<ExprNode::BinaryOpNode>
                (getOperator(), exprNode1, exprNode2), toString(startIndex, endIndex));
        } else if (isFactor() && isPrevTokenStartBracket) {
            throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
        } else if (isExprOperator() || isTermOperator() || isFactor()) {
            isPrevTokenNonBracket = true;
            isPrevTokenStartBracket = false;
        } else if (isIllegalArithmeticSplChar()) {
            throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
        }

        // Pop brackets if they are together
        isPrevBracketEndBracket = true;
        isPrevBracketStartBracket = false;
        endBracketStack.emplace_back(index);

        index--;
    }

    if (numOfBrackets != 0) {
        throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
    }

    return parseTerm(startIndex, endIndex);
}

OperatorType Parser::getOperator() {
    if (isValueOf(ADD_OPERATOR)) {
        return OperatorType::ADD;
    } else if (isValueOf(SUBTRACT_OPERATOR)) {
        return OperatorType::SUBTRACT;
    } else if (isValueOf(MULTIPLY_OPERATOR)) {
        return OperatorType::MULTIPLY;
    } else if (isValueOf(DIVIDE_OPERATOR)) {
        return OperatorType::DIVIDE;
    } else if (isValueOf(MOD_OPERATOR)) {
        return OperatorType::MOD;
    }

    throw SourceParserException(ParserInvalidOpExceptionMessage);
}

bool Parser::isIllegalArithmeticSplChar() {
    return isTypeOf(TokenType::TOKEN_SPECIAL_CHAR) && !isExprOperator() && !isTermOperator()
        && !isValueOf(BRACKETS_START) && !isValueOf(BRACKETS_END);
}

bool Parser::isExprOperator() {
    return isValueOf(ADD_OPERATOR) || isValueOf(SUBTRACT_OPERATOR);
}

bool Parser::isTermOperator() {
    return isValueOf(MULTIPLY_OPERATOR) || isValueOf(DIVIDE_OPERATOR) || isValueOf(MOD_OPERATOR);
}

std::shared_ptr<ExprNode> Parser::parseTerm(int startIndex, int endIndex) {
    index = endIndex;

    // Parse single name/integer factor
    if (startIndex >= endIndex) {
        return parseFactor(startIndex, endIndex);
    }

    int numOfBrackets = 0;
    bool isPrevTokenStartBracket = false;
    bool isPrevTokenNonBracket = true;
    bool isPrevBracketStartBracket = false;
    bool isPrevBracketEndBracket = false;

    std::vector<int> endBracketStack;

    while (!isTypeOf(TokenType::TOKEN_END_OF_FILE) && index >= startIndex) {
        if (isValueOf(BRACKETS_END)) {
            if (isPrevTokenStartBracket) {
                throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
            }

            isPrevTokenNonBracket = false;
            isPrevTokenStartBracket = false;
            numOfBrackets--;
            isPrevBracketEndBracket = true;
            isPrevBracketStartBracket = false;
            endBracketStack.emplace_back(index);
        } else if (isValueOf(BRACKETS_START)) {
            if (!isPrevTokenNonBracket && !isPrevTokenStartBracket) {
                throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
            }

            isPrevTokenNonBracket = false;
            isPrevTokenStartBracket = true;
            numOfBrackets++;

            if (endBracketStack.at(0) == endIndex && endBracketStack.size() == 1
                && index == startIndex && numOfBrackets == 0) {
                return parseExprNode(startIndex + 1, endIndex - 1);
            }

            if (endBracketStack.empty()) {
                throw SourceParserException(ParserInvalidExprFormatExceptionMessage);
            }

            isPrevBracketEndBracket = false;
            isPrevBracketStartBracket = true;
            endBracketStack.pop_back();
        } else if (isTermOperator() && numOfBrackets == 0) {
            int currIndex = index;
            auto exprNode1 = parseExprNode(startIndex, currIndex - 1);
            auto exprNode2 = parseExprNode(currIndex + 1, endIndex);
            index = currIndex;
            return std::make_shared<ExprNode>(std::make_shared<ExprNode::BinaryOpNode>
                (getOperator(), exprNode1, exprNode2), toString(startIndex, endIndex));
        } else if (isFactor() && isPrevTokenStartBracket) {
            throw SourceParserException(ParserInvalidTermFormatExceptionMessage);
        } else if (isExprOperator() || isTermOperator() || isFactor()) {
            isPrevTokenNonBracket = true;
            isPrevTokenStartBracket = false;
        }  else if (isIllegalArithmeticSplChar()) {
            throw SourceParserException(ParserInvalidTermFormatExceptionMessage);
        }

        index--;
    }

    if (numOfBrackets != 0) {
        throw SourceParserException(ParserInvalidTermFormatExceptionMessage);
    }

    return parseExprNode(startIndex, endIndex);
}

bool Parser::isFactor() {
    return isTypeOf(TokenType::TOKEN_NAME) || isTypeOf(TokenType::TOKEN_INTEGER);
}

std::shared_ptr<ExprNode> Parser::parseFactor(int startIndex, int endIndex) {
    if (startIndex != endIndex) {
        throw SourceParserException(ParserInvalidFactorLengthExceptionMessage);
    }

    if (isTypeOf(TokenType::TOKEN_NAME)) {
        return std::make_shared<ExprNode>(parseNext(TokenType::TOKEN_NAME)->getValue(),
            ExprNodeType::FACTOR_VARIABLE);
    } else if (isTypeOf(TokenType::TOKEN_INTEGER)) {
        return std::make_shared<ExprNode>(parseNext(TokenType::TOKEN_INTEGER)->getValue()
            , ExprNodeType::FACTOR_CONSTANT);
    }

    throw SourceParserException(ParserInvalidFactorExceptionMessage);
}

std::shared_ptr<AssignNode> Parser::parseAssign(std::shared_ptr<Token> nameToken) {
    stmtIndex++;
    parseNext(ASSIGN_OPERATOR);

    int currIndex = index;
    while (!isValueOf(STMT_END) && !isTypeOf(TokenType::TOKEN_END_OF_FILE)) {
        getNext();
    }
    int newIndex = index - 1;
    auto exprNode = parseExprNode(currIndex, newIndex);
    index = newIndex + 1;
    parseNext(STMT_END);

    return std::make_shared<AssignNode>(stmtIndex, nameToken->getValue(), exprNode);
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
