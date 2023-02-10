#include "Token.h"
#include <string>

Token::Token(TokenType type, std::string value) : type(type), value(value) {}

std::string Token::getValue() { return this->value; }

TokenType Token::getType() { return this->type; }

bool Token::operator==(const Token& token) const {
    return this->type == token.type && this->value == token.value;
}
