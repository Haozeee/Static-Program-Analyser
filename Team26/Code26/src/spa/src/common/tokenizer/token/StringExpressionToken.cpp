#include "StringExpressionToken.h"

#include <utility>

StringExpressionToken::StringExpressionToken(std::string value) : Token(
        TokenType::TOKEN_STRING_EXPRESSION, std::move(value)) {}
