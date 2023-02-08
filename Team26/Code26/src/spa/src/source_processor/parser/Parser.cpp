#include "Parser.h"
#include <memory>
#include <optional>
#include <string>
#include <utility>

#define INITIAL_STMT_INDEX 0
#define STMTLIST_START "{"
#define STMTLIST_END "}"
#define BRACKETS_START "("
#define BRACKETS_END ")"
#define STMT_END ";"
#define ASSIGN_OPERATOR "="
#define MULTIPLY_OPERATOR '*'
#define DIVIDE_OPERATOR '/'
#define MOD_OPERATOR '%'
#define ADD_OPERATOR '+'
#define SUBTRACT_OPERATOR '-'
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
    std::string condExprStr = "";

    while (!isValueOf(BRACKETS_END)) {
        condExprStr += getToken()->getValue();
        getNext();
    }
    std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(condExprStr);
    parseNext(BRACKETS_END);

    stmtIndex++;

    parseNext(STMTLIST_START);
    std::shared_ptr<StmtListNode> stmtListNode = parseStmtList();
    parseNext(STMTLIST_END);

    return std::make_shared<WhileNode>(stmtIndex, condExprNode, stmtListNode);
 }

 std::shared_ptr<IfNode> Parser::parseIf() {
     parseNext(BRACKETS_START);
     std::string condExprStr = "";

     while (!isValueOf(BRACKETS_END)) {
         condExprStr += getToken()->getValue();
         getNext();
     }
     std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(condExprStr);
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

std::shared_ptr<CondExprNode> Parser::parseCondExprNode(std::string condExpr) {
    if (condExpr.length() == 0) {
        // TODO(oviya): throw error
    }

    // If cond_expr = !(cond_expr)
    if (condExpr.length() > 3 && condExpr[0] == NOT_OPERATOR[0] && condExpr[1] == BRACKETS_START[0]
        && condExpr.back() == BRACKETS_END[0]) {
        std::shared_ptr<CondExprNode> condExprNode = parseCondExprNode(condExpr.substr(2, condExpr.length() - 2));
        return std::make_shared<CondExprNode>(std::make_pair(UnaryCondExprOperatorType::OPERATOR_NOT, condExprNode));
    }

    // If cond_expr = rel_expr
    if (condExpr.back() != BRACKETS_END[0]) {
        return std::make_shared<CondExprNode>(parseRelExpr(condExpr));
    }

    // Check for '&&' operator.
    std::optional<BinaryCondExprOperatorType> opType = std::nullopt; 
    std::size_t opPos = condExpr.find(BRACKETS_END[0] + AND_OPERATOR[0]
        + BRACKETS_START[0]);
    if (opPos != std::string::npos) {
        if (opPos <= 1 || opPos >= condExpr.length() - 5) {
            // TODO(oviya): throw error
        }

        opType = BinaryCondExprOperatorType::OPERATOR_AND;
    }

    // Check for '||' operator.
    if (!opType.has_value()) {
        opPos = condExpr.find(BRACKETS_END[0] + OR_OPERATOR[0] + BRACKETS_START[0]);
        if (opPos != std::string::npos) {
            if (opPos <= 1 || opPos >= condExpr.length() - 5) {
                // TODO(oviya): throw error
            }

            opType = BinaryCondExprOperatorType::OPERATOR_OR;
        }
    }

    if (!opType.has_value()) {
        // TODO(oviya): throw error
    }

    std::string firstSubStr = condExpr.substr(0, opPos - 1);
    std::string secondSubStr =condExpr.substr(opPos + 1, condExpr.length());

    auto condExprNode1 = parseCondExprNode(firstSubStr);
    auto condExprNode2 = parseCondExprNode(secondSubStr);

    return std::make_shared<CondExprNode>(std::make_tuple(opType.value(), condExprNode1, condExprNode2));

}

std::shared_ptr<RelExpr> Parser::parseRelExpr(std::string relExpr) {
    if (relExpr.length() == 0) {
        // TODO(oviya): throw error
    }

    std::optional<RelExprOperatorType> opType;
    
    // Check for '>' operator.
    std::size_t opPos = relExpr.find(GT_OPERATOR);
    if (opPos != std::string::npos) {
        if (opPos == 0 || opPos == relExpr.length() - 1) {
            // TODO(oviya): throw error
        }

        opType = RelExprOperatorType::OPERATOR_GT;
    } 

    // Check for '>=' operator.
    if (!opType.has_value()) {
        opPos = relExpr.find(GTE_OPERATOR);
        if (opPos != std::string::npos) {
            if (opPos == 0 || opPos == relExpr.length() - 1) {
                // TODO(oviya): throw error
            }

            opType = RelExprOperatorType::OPERATOR_GTE;
        }
    }

    // Check for '<' operator.
    if (!opType.has_value()) {
        opPos = relExpr.find(LT_OPERATOR);
        if (opPos != std::string::npos) {
            if (opPos == 0 || opPos == relExpr.length() - 1) {
                // TODO(oviya): throw error
            }

            opType = RelExprOperatorType::OPERATOR_LT;
        }
    }

    // Check for '<=' operator.
    if (!opType.has_value()) {
        opPos = relExpr.find(LTE_OPERATOR);
        if (opPos != std::string::npos) {
            if (opPos == 0 || opPos == relExpr.length() - 1) {
                // TODO(oviya): throw error
            }

            opType = RelExprOperatorType::OPERATOR_LTE;
        }
    }

    // Check for '==' operator.
    if (!opType.has_value()) {
        opPos = relExpr.find(EQ_OPERATOR);
        if (opPos != std::string::npos) {
            if (opPos == 0 || opPos == relExpr.length() - 1) {
                // TODO(oviya): throw error
            }

            opType = RelExprOperatorType::OPERATOR_EQ;
        }
    }

    // Check for '!=' operator.
    if (!opType.has_value()) {
        opPos = relExpr.find(NEQ_OPERATOR);
        if (opPos != std::string::npos) {
            if (opPos == 0 || opPos == relExpr.length() - 1) {
                // TODO(oviya): throw error
            }

            opType = RelExprOperatorType::OPERATOR_NEQ;
        }
    }

    if (!opType.has_value()) {
        // TODO(oviya): throw error
    }

    std::string firstSubStr = relExpr.substr(0, opPos - 1);
    std::string secondSubStr = relExpr.substr(opPos + 1, relExpr.length());

    auto exprNode1 = parseExprNode(firstSubStr);
    auto exprNode2 = parseExprNode(secondSubStr);

    return std::make_shared<RelExpr>(std::make_tuple(opType.value(), exprNode1, exprNode2));
}

std::shared_ptr<ExprNode> Parser::parseExprNode(std::string expr) {
    std::string firstSubStr = "", secondSubStr = "";
    std::optional<ExprOperatorType> opType;

    std::string* currStr = &firstSubStr;

    for (char& c : expr) {
        if (c == ADD_OPERATOR) {
            if (firstSubStr.empty()) {
                // TODO(oviya): throw error
            }

            opType = ExprOperatorType::OPERATOR_ADD;
            currStr = &secondSubStr;
        } else if (c == SUBTRACT_OPERATOR) {
            if (firstSubStr.empty()) {
                // TODO(oviya): throw error
            }

            opType = ExprOperatorType::OPERATOR_SUBTRACT;
            currStr = &secondSubStr;
        }
    }

    if (opType.has_value()) {
        if (secondSubStr.empty()) {
            // TODO(oviya): throw error
        }

        std::pair<ExprOperatorType, std::shared_ptr<ExprNode>> optionalParams =
            std::make_pair(opType.value(), parseExprNode(firstSubStr));
        getNext(); // Skip operator
        return std::make_shared<ExprNode>(parseTermNode(secondSubStr), optionalParams);
    }

    return std::make_shared<ExprNode>(parseTermNode(firstSubStr), std::nullopt);
}

std::shared_ptr<TermNode> Parser::parseTermNode(std::string term) {
    std::string firstSubStr = "", secondSubStr = "";
    std::optional<TermOperatorType> opType = std::nullopt;

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
    }

    if (opType.has_value()) {
        if (secondSubStr.empty()) {
            // TODO(oviya): throw error
        }
        
        std::pair<TermOperatorType, std::shared_ptr<TermNode>> optionalParams
            = std::make_pair(opType.value(), parseTermNode(firstSubStr));
        getNext(); // Skip operator
        return std::make_shared<TermNode>(parseFactor(secondSubStr), optionalParams);
    }

    return std::make_shared<TermNode>(parseFactor(firstSubStr), std::nullopt);
}

std::shared_ptr<Factor> Parser::parseFactor(std::string factor) {
    if (factor.length() == 0) {
        // TODO(oviya): throw error
    }

    if (factor[0] == BRACKETS_START[0] && factor.back() == BRACKETS_END[0]) {
        return parseFactor(factor.substr(1,factor.length()-2));
    } 

    std::shared_ptr<Token> token;

    if (isTypeOf(TokenType::TOKEN_INTEGER)) {
        token = parseNext(TokenType::TOKEN_INTEGER);
    } else if (isTypeOf(TokenType::TOKEN_NAME)) {
        token = parseNext(TokenType::TOKEN_NAME);
    } else {
        // TODO(oviya): throw exception
    }

    return std::make_shared<Factor>(token->getValue());
}

std::shared_ptr<AssignNode> Parser::parseAssign(std::shared_ptr<Token> nameToken) {
    parseNext(ASSIGN_OPERATOR);
    std::string expr = "";
    ExprNode exprNode = *parseExprNode(expr);
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
