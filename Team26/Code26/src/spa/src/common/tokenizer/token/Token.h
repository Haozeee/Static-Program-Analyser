#pragma once

#include <string>

// enum class is preferred, values do not implicitly convert to other types
enum class TokenType {
    TOKEN_NAME,
    TOKEN_INTEGER,
    TOKEN_END_OF_FILE,
    TOKEN_SPECIAL_CHAR,
    TOKEN_STRING_EXPRESSION
};

// Base Class Abstract Class
class Token {
 protected:
    const std::string value;
    TokenType type;

 public:
    Token(TokenType type, std::string value);

    // TODO(zhengteck): Reconsider getter and setters is required.
    TokenType getType();
    std::string getValue();
};
