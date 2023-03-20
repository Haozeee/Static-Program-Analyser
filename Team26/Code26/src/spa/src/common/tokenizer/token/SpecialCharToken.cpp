#include "SpecialCharToken.h"

#include <utility>

SpecialCharToken::SpecialCharToken(std::string value) : Token(TokenType::TOKEN_SPECIAL_CHAR, std::move(value)) {}
