#include "IntegerToken.h"

#include <utility>

IntegerToken::IntegerToken(std::string value) : Token(TokenType::TOKEN_INTEGER, std::move(value)) {}
