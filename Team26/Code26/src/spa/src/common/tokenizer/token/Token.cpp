#include "Token.h"
#include <string>
#include <utility>

Token::Token(TokenType type, std::string value) : type(type), value(std::move(value)) {}

std::string Token::getValue() { return this->value; }

TokenType Token::getType() { return this->type; }

bool Token::operator==(const Token& token) const {
    return this->type == token.type && this->value == token.value;
}

bool Token::isIntegerOrNameToken() const {
    return this->type == TokenType::TOKEN_NAME || this->type == TokenType::TOKEN_INTEGER;
}
