#include "Parser.h"

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

    while (getToken()->getValue() != STMTLIST_END) {
        if (getToken()->getType() != TokenType::TOKEN_NAME) {
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
        } else if (nameToken->getValue() == WHILE_KEYWORD) {
            stmtNode = parseWhile();
        } else if (nameToken->getValue() == IF_KEYWORD) {
            stmtNode = parseIf();
        } else if (isValueOf(ASSIGN_OPERATOR)) {
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

std::shared_ptr<WhileNode> Parser::parseWhile() {
    parseNext(BRACKETS_START);
    int oldIndex = index;
    int numOfBrackets = 1;
    while (getToken()->getType() != TokenType::TOKEN_END_OF_FILE) {
        if (getToken()->getValue() == BRACKETS_START) {
            numOfBrackets++;
        } else if (getToken()->getValue() == BRACKETS_END) {
            numOfBrackets--;
        }

        if (getToken()->getValue() == BRACKETS_END && numOfBrackets == 0) {
            break;
        }
        getNext();
    }
    int newIndex = index - 1;
    std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(oldIndex, newIndex);
    index = newIndex + 1;
    parseNext(BRACKETS_END);

    stmtIndex++;

    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> stmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    return std::make_shared<WhileNode>(stmtIndex, condExprNode, stmtListNode);
}

std::shared_ptr<IfNode> Parser::parseIf() {
    parseNext(BRACKETS_START);
    int oldIndex = index;
    int numOfBrackets = 1;
    while (getToken()->getType() != TokenType::TOKEN_END_OF_FILE) {
        if (getToken()->getValue() == BRACKETS_START) {
            numOfBrackets++;
        } else if (getToken()->getValue() == BRACKETS_END) {
            numOfBrackets--;
        }

        if (getToken()->getValue() == BRACKETS_END && numOfBrackets == 0) {
            break;
        }
        getNext();
    }
    int newIndex = index - 1;
    std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(oldIndex, newIndex);
    index = newIndex + 1;
    parseNext(BRACKETS_END);

    std::shared_ptr<Token> nameToken = parseNext(TokenType::TOKEN_NAME);
    if (nameToken->getValue() != THEN_KEYWORD) {
        // TODO(oviya): throw error
    }

    stmtIndex++;

    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> thenStmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    nameToken = parseNext(TokenType::TOKEN_NAME);
    if (nameToken->getValue() != ELSE_KEYWORD) {
        // TODO(oviya): throw error
    }

    stmtIndex++;

    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> elseStmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    return std::make_shared<IfNode>(stmtIndex, condExprNode, thenStmtListNode, elseStmtListNode);
}

std::shared_ptr<CondExprNode> Parser::parseCondExprNode(int startIndex, int endIndex) {
    // If cond_expr = rel_expr
    index = endIndex;
    if (getToken()->getValue() != BRACKETS_END) {
        return std::make_shared<CondExprNode>(parseRelExpr(startIndex, endIndex),
            toString(startIndex, endIndex));
    }

    // If cond_expr = !(cond_expr)
    index = startIndex;
    if (endIndex >= startIndex + 3 && getToken()->getValue() == NOT_OPERATOR
        && getNext()->getValue() == BRACKETS_START) {
        std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(startIndex + 2, endIndex - 1);
        CondExprNode c = *condExprNode;
        return std::make_shared<CondExprNode>(std::make_tuple(UnaryCondOperatorType::NOT, condExprNode),
            toString(startIndex, endIndex));
    }

    // If cond_expr = (cond_expr) && (cond_expr) or cond_expr = (cond_expr) || (cond_expr)
    index = startIndex;
    if (getToken()->getValue() != BRACKETS_START) {
        // TODO(oviya): throw error
    }

    int numOfBrackets = 0;
    while (getToken()->getType() != TokenType::TOKEN_END_OF_FILE && index <= endIndex) {
        if (getToken()->getValue() == AND_OPERATOR) {
            // Check if cond_expr = (cond_expr) && (cond_expr)
            int currIndex = index;
            index--;
            if (getToken()->getValue() != BRACKETS_END) {
                // TODO(oviya): throw error
            }
            index += 2;
            if (getToken()->getValue() != BRACKETS_START) {
                // TODO(oviya): throw error
            }
            index = currIndex;

            auto condExprNode1 = parseCondExprNode(startIndex + 1, index - 2);
            auto condExprNode2 = parseCondExprNode(index + 2, endIndex - 1);

            return std::make_shared<CondExprNode>(std::make_tuple(BinaryCondOperatorType::AND,
                condExprNode1, condExprNode2), toString(startIndex, endIndex));
        } else if (getToken()->getValue() == OR_OPERATOR) {
            // Check if cond_expr = (cond_expr) || (cond_expr)
            int currIndex = index;
            index--;
            if (getToken()->getValue() != BRACKETS_END) {
                // TODO(oviya): throw error
            }
            index += 2;
            if (getToken()->getValue() != BRACKETS_START) {
                // TODO(oviya): throw error
            }
            index = currIndex;

            auto condExprNode1 = parseCondExprNode(startIndex + 1, index - 2);
            auto condExprNode2 = parseCondExprNode(index + 2, endIndex - 1);
            return std::make_shared<CondExprNode>(std::make_tuple(BinaryCondOperatorType::OR,
                condExprNode1, condExprNode2), toString(startIndex, endIndex));
        } else if (getToken()->getValue() == BRACKETS_START) {
            numOfBrackets++;
        } else if (getToken()->getValue() == BRACKETS_END) {
            numOfBrackets--;
        }
        getNext();
    }

    // TODO(oviya): throw error
}

std::shared_ptr<RelExpr> Parser::parseRelExpr(int startIndex, int endIndex) {
    index = startIndex;
    std::optional<RelExprOperatorType> opType = std::nullopt;

    while (getToken()->getType() != TokenType::TOKEN_END_OF_FILE && index <= endIndex) {
        if (getToken()->getValue() == GT_OPERATOR) {
            opType = RelExprOperatorType::GT;
            break;
        } else if (getToken()->getValue() == GTE_OPERATOR) {
            opType = RelExprOperatorType::GTE;
            break;
        } else if (getToken()->getValue() == LT_OPERATOR) {
            opType = RelExprOperatorType::LT;
            break;
        } else if (getToken()->getValue() == LTE_OPERATOR) {
            opType = RelExprOperatorType::LTE;
            break;
        } else if (getToken()->getValue() == EQ_OPERATOR) {
            opType = RelExprOperatorType::EQ;
            break;
        } else if (getToken()->getValue() == NEQ_OPERATOR) {
            opType = RelExprOperatorType::NEQ;
            break;
        }
        getNext();
    }

    if (!opType.has_value()) {
        // TODO(oviya): throw error
    }

    auto exprNode1 = parseExprNode(startIndex, index - 1);
    auto exprNode2 = parseExprNode(index + 1, endIndex);

    return std::make_shared<RelExpr>(std::make_tuple(opType.value(), exprNode1, exprNode2));
}

std::shared_ptr<ExprNode> Parser::parseExprNode(int startIndex, int endIndex) {
    index = startIndex;

    // Parse single name/integer factor
    if (startIndex == endIndex) {
        if (isTypeOf(TokenType::TOKEN_NAME)) {
            return std::make_shared<ExprNode>(parseNext(TokenType::TOKEN_NAME)->getValue(),
                ExprNodeType::FACTOR_VARIABLE);
        } else if (isTypeOf(TokenType::TOKEN_INTEGER)) {
            return std::make_shared<ExprNode>(parseNext(TokenType::TOKEN_INTEGER)->getValue()
                , ExprNodeType::FACTOR_CONSTANT);
        }

        // TODO(oviya): throw error
    }

    int numOfBrackets = 0;
    int firstBracketIndex = endIndex + 1;
    int lastBracketIndex = startIndex - 1;
    bool isprevTokenEndBracket = false;

    while (getToken()->getType() != TokenType::TOKEN_END_OF_FILE && index <= endIndex) {
        if (getToken()->getValue() == BRACKETS_START) {
            if (isprevTokenEndBracket) {
                // TODO(oviya): throw error
            }

            numOfBrackets++;
            firstBracketIndex = (index < firstBracketIndex) ? index : firstBracketIndex;
        } else if (getToken()->getValue() == BRACKETS_END) {
            isprevTokenEndBracket = true;
            numOfBrackets--;
            lastBracketIndex = (index > lastBracketIndex) ? index : lastBracketIndex;
        } else if (getToken()->getValue() == ADD_OPERATOR && numOfBrackets == 0) {
            auto exprNode1 = parseExprNode(startIndex, index - 1);
            auto exprNode2 = parseExprNode(index + 1, endIndex);
            return std::make_shared<ExprNode>(std::make_shared<ExprNode::BinaryOpNode>
                (OperatorType::ADD, exprNode1, exprNode2), toString(startIndex, endIndex));
        } else if (getToken()->getValue() == SUBTRACT_OPERATOR && numOfBrackets == 0) {
            auto exprNode1 = parseExprNode(startIndex, index - 1);
            auto exprNode2 = parseExprNode(index + 1, endIndex);
            return std::make_shared<ExprNode>(std::make_shared<ExprNode::BinaryOpNode>
                (OperatorType::SUBTRACT, exprNode1, exprNode2), toString(startIndex, endIndex));
        } else if (getToken()->getType() == TokenType::TOKEN_NAME ||
            getToken()->getType() == TokenType::TOKEN_INTEGER) {
            if (isprevTokenEndBracket) {
                // TODO(oviya): throw error
            }
        } else if (getToken()->getType() == TokenType::TOKEN_SPECIAL_CHAR) {
            if (getToken()->getValue() != MULTIPLY_OPERATOR || getToken()->getValue() != DIVIDE_OPERATOR
                || getToken()->getValue() != MOD_OPERATOR || getToken()->getValue() != ADD_OPERATOR
                || getToken()->getValue() != SUBTRACT_OPERATOR) {
                // TODO(oviya): throw error
            }
        }
        getNext();
    }

    if (numOfBrackets != 0) {
        // TODO(oviya): throw error
    }

    if (firstBracketIndex == startIndex && lastBracketIndex == endIndex) {
        return parseExprNode(startIndex + 1, endIndex - 1);
    }

    return parseTerm(startIndex, endIndex);
}

std::shared_ptr<ExprNode> Parser::parseTerm(int startIndex, int endIndex) {
    index = startIndex;

    // Parse single name/integer factor
    if (startIndex == endIndex) {
        if (getToken()->getType() == TokenType::TOKEN_NAME) {
            return std::make_shared<ExprNode>(parseNext(TokenType::TOKEN_NAME)->getValue()
                , ExprNodeType::FACTOR_VARIABLE);
        } else if (getToken()->getType() == TokenType::TOKEN_INTEGER) {
            return std::make_shared<ExprNode>(parseNext(TokenType::TOKEN_INTEGER)->getValue()
                , ExprNodeType::FACTOR_CONSTANT);
        }

        // TODO(oviya): throw error
    }

    int numOfBrackets = 0;
    int firstBracketIndex = 0;
    int lastBracketIndex = 0;

    while (getToken()->getType() != TokenType::TOKEN_END_OF_FILE && index <= endIndex) {
        if (getToken()->getValue() == BRACKETS_START) {
            numOfBrackets++;
            firstBracketIndex = (numOfBrackets == 0) ? index : firstBracketIndex;
        } else if (getToken()->getValue() == BRACKETS_END) {
            numOfBrackets--;
            lastBracketIndex = (numOfBrackets == 0) ? index : lastBracketIndex;
        } else if (getToken()->getValue() == MULTIPLY_OPERATOR && numOfBrackets == 0) {
            auto exprNode1 = parseExprNode(startIndex, index - 1);
            auto exprNode2 = parseExprNode(index + 1, endIndex);
            return std::make_shared<ExprNode>(std::make_shared<ExprNode::BinaryOpNode>
                (OperatorType::MULTIPLY, exprNode1, exprNode2), toString(startIndex, endIndex));
        } else if (getToken()->getValue() == DIVIDE_OPERATOR && numOfBrackets == 0) {
            auto exprNode1 = parseExprNode(startIndex, index - 1);
            auto exprNode2 = parseExprNode(index + 1, endIndex);
            return std::make_shared<ExprNode>(std::make_shared<ExprNode::BinaryOpNode>
                (OperatorType::DIVIDE, exprNode1, exprNode2), toString(startIndex, endIndex));
        } else if (getToken()->getValue() == MOD_OPERATOR && numOfBrackets == 0) {
            auto exprNode1 = parseExprNode(startIndex, index - 1);
            auto exprNode2 = parseExprNode(index + 1, endIndex);
            return std::make_shared<ExprNode>(std::make_shared<ExprNode::BinaryOpNode>
                (OperatorType::MOD, exprNode1, exprNode2), toString(startIndex, endIndex));
        }
        getNext();
    }

    if (numOfBrackets != 0) {
        // TODO(oviya): throw error
    }

    if (firstBracketIndex == startIndex && lastBracketIndex == endIndex) {
        return parseExprNode(startIndex + 1, endIndex - 1);
    }

    return parseTerm(startIndex, endIndex);
}

std::shared_ptr<AssignNode> Parser::parseAssign(std::shared_ptr<Token> nameToken) {
    parseNext(ASSIGN_OPERATOR);

    int currIndex = index;
    while (getToken()->getValue() != STMT_END) {
        getNext();
    }
    int newIndex = index - 1;
    auto exprNode = parseExprNode(currIndex, newIndex);
    index = newIndex + 1;
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
