#pragma once

#include <string>

// enum class is preferred, values do not implicitly convert to other types
enum class TokenType {
    NAME,
    INTEGER,
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
