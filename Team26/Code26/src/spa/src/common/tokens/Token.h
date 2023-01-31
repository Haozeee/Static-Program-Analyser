#pragma once

#include <string>

// enum class is preferred, values do not implicitly convert to other types
enum class TokenType {
    TOKEN_NAME,
    TOKEN_INTEGER,
    TOKEN_END_OF_FILE,
    TOKEN_SPECIAL_CHAR
};

// Base Class Abstract Class
class Token {
 protected:
    TokenType type;
    std::string value;

 public:
    Token(TokenType type, std::string value);

    TokenType getType() { return this->type; }

    std::string getValue() { return this->value; }
};
