#include "NameToken.h"

#include <utility>

NameToken::NameToken(std::string value) : Token(TokenType::TOKEN_NAME, std::move(value)) {}
