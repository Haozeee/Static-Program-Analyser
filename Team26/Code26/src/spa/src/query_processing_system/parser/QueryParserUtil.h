#pragma once

#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include "common/exception/ExceptionMessage.h"
#include "common/tokenizer/token/Token.h"

class QueryParserUtil {
 private:
    static std::string trim(std::string);

    static std::shared_ptr<Token> tokenizeName(const std::string&, int*);

    static std::shared_ptr<Token> tokenizeInteger(const std::string&, int*);

    static std::shared_ptr<Token> tokenizeOperator(const std::string&, int*);

    static std::shared_ptr<Token> tokenizeBracket(int*, char);

    static std::vector<std::shared_ptr<Token>> tokenize(const std::string&);

    static bool validateNameOrInteger(bool*, std::stack<std::shared_ptr<Token>>*, std::shared_ptr<Token>);

    static bool validateOperator(std::shared_ptr<Token>, bool*, std::stack<std::shared_ptr<Token>>*);

    static bool validateCloseBracket(std::stack<std::shared_ptr<Token>>*, std::stack<std::shared_ptr<Token>>*);

    static bool handleRemainingTerms(std::stack<std::shared_ptr<Token>>*, std::stack<std::shared_ptr<Token>>*);

 public:
    static bool isValidIdent(std::string);

    static bool isValidStringExpression(std::string expr);
};
