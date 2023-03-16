#include "QueryParserUtil.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"

std::unordered_set<char> operators = std::unordered_set<char>({'+', '-', '*', '/', '%' });

std::string QueryParserUtil::trim(std::string value) {
    auto len = value.size();
    int left = 0;
    int right = len - 1;

    while (left < len && value.at(left) == ' ') {
        left++;
    }
    if (left == len) {
        return "";
    }

    while (right >= 0 && value.at(right) == ' ') {
        right--;
    }
    int subStrLen = right - left + 1;

    return value.substr(left, subStrLen);
}

bool QueryParserUtil::isValidIdent(std::string string) {
    std::string str = trim(string);
    // Ident cannot be empty
    if (str.empty()) {
        return false;
    }

    // Ident can only start with letter
    if (!isalpha(str.at(0))) {
        return false;
    }

    // Ident can only contain letters or digits
    for (int i = 1; i < str.size(); i++) {
        char c = str.at(i);
        if (!isalnum(c)) {
            return false;
        }
    }

    return true;
}

bool QueryParserUtil::handleRemainingTerms(std::stack<std::shared_ptr<Token>>* term,
                                           std::stack<std::shared_ptr<Token>>* op) {
    while (!op->empty()) {
        std::string cur = op->top()->getValue();
        op->pop();

        if (operators.find(cur.at(0)) == operators.end()) {
            return false;
        }

        if (term->size() < 2) {
            return false;
        } else {
            term->pop();
        }
    }

    if (term->size() > 1) {
        return false;
    }

    return true;
}

std::shared_ptr<Token> QueryParserUtil::tokenizeInteger(const std::string& expr, int* index) {
    int num = 0;
    bool isFirst = true;
    while (*index < expr.size() && isdigit(expr.at(*index))) {
        // Lexical token grammar rules: no leading zeroes
        if (!isFirst && num == 0) {
            throw QueryParserException(QueryParserInvalidLanguageRules);
        }

        num = (num * 10) + (expr.at(*index) - '0');
        *index += 1;
        isFirst = false;
    }

    return std::make_shared<Token>(TokenType::TOKEN_INTEGER, std::to_string(num));
}

std::shared_ptr<Token> QueryParserUtil::tokenizeName(const std::string& expr, int* index) {
    std::string var;
    while (*index < expr.size() && isalnum(expr.at(*index))) {
        var += expr.at(*index);
        *index += 1;
    }

    return std::make_shared<Token>(TokenType::TOKEN_NAME, var);
}

std::shared_ptr<Token> QueryParserUtil::tokenizeOperator(const std::string& expr, int* index) {
    std::string op{expr.at(*index)};
    *index += 1;
    return std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, op);
}

std::shared_ptr<Token> QueryParserUtil::tokenizeBracket(int* index, char bracketChar) {
    *index += 1;
    std::string bracket{bracketChar};
    return std::make_shared<Token>(TokenType::TOKEN_SPECIAL_CHAR, bracket);
}

std::vector<std::shared_ptr<Token>> QueryParserUtil::tokenize(const std::string& expr) {
    std::vector<std::shared_ptr<Token>> res;

    int index = 0;

    while (index < expr.size()) {
        char c = expr.at(index);
        if (isspace(c)) {
            index++;
            continue;
        }

        if (isdigit(c)) {
            auto intToken = tokenizeInteger(expr, &index);
            res.push_back(intToken);
            continue;
        }

        if (isalpha(c)) {
            auto nameToken = tokenizeName(expr, &index);
            res.push_back(nameToken);
            continue;
        }

        if (operators.find(c) != operators.end()) {
            auto opToken = tokenizeOperator(expr, &index);
            res.push_back(opToken);
            continue;
        }

        if (c == '(' || c == ')') {
            auto bracketToken = tokenizeBracket(&index, c);
            res.push_back(bracketToken);
            continue;
        }

        throw QueryParserException(QueryParserInvalidLanguageRules);
    }
    return res;
}

bool QueryParserUtil::validateNameOrInteger(bool* isOperatorBefore, std::stack<std::shared_ptr<Token>>* term,
                                            std::shared_ptr<Token> token) {
    term->push(token);
    if (!*isOperatorBefore) {
        return false;
    }

    *isOperatorBefore = false;
    return true;
}

bool QueryParserUtil::validateOperator(std::shared_ptr<Token> token, bool* isOperatorBefore,
                            std::stack<std::shared_ptr<Token>>* op) {
    if (*isOperatorBefore) {
        return false;
    }

    *isOperatorBefore = true;
    op->push(token);
    return true;
}

bool QueryParserUtil::validateCloseBracket(std::stack<std::shared_ptr<Token>>* term,
                                           std::stack<std::shared_ptr<Token>>* op) {
    bool flag = true;

    while (!op->empty()) {
        char cur = op->top()->getValue().at(0);
        op->pop();
        if (cur == '(') {
            flag = false;
            break;
        } else {
            if (term->size() < 2) {
                return false;
            } else {
                term->pop();
            }
        }
    }

    return !flag;
}

bool QueryParserUtil::isValidStringExpression(std::string expr) {
    if (expr.empty()) {
        return false;
    }

    std::vector<std::shared_ptr<Token>> tokens;
    try {
        tokens = tokenize(expr);
    } catch (QueryParserException&) {
        return false;
    }

    std::stack<std::shared_ptr<Token>> var;
    std::stack<std::shared_ptr<Token>> op;
    bool isOperatorBefore = true;
    bool containsVariables = false;

    for (auto token : tokens) {
        if (token->getType() == TokenType::TOKEN_NAME || token->getType() == TokenType::TOKEN_INTEGER) {
            if (!validateNameOrInteger(&isOperatorBefore, &var, token)) {
                return false;
            }
            containsVariables = true;
        } else if (operators.find(token->getValue().at(0)) != operators.end()) {
            if (!validateOperator(token, &isOperatorBefore, &op)) {
                return false;
            }
        } else if (token->getValue() == "(") {
            op.push(token);
        } else if (token->getValue() == ")") {
            if (!validateCloseBracket(&var, &op)) {
                return false;
            }
        } else {
            return false;
        }
    }

    if (!containsVariables) {
        return false;
    }

    return handleRemainingTerms(&var, &op);
}
