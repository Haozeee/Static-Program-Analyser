#include "StringExpressionToken.h"

StringExpressionToken::StringExpressionToken(std::string value) : Token(TokenType::TOKEN_STRING_EXPRESSION, value) {}
