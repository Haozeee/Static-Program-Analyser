#include "Parser.h"

#include <utility>
#include <string>

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens) : tokens(std::move(tokens)) {}

bool Parser::hasNext() {
    return index < tokens.size() - 1;
}

std::shared_ptr<Token> Parser::getToken() {
    return tokens[index];
}

std::shared_ptr<Token> Parser::getNext() {
    return tokens[index++];
}

std::shared_ptr<Token> Parser::getEOF() {
    return tokens[tokens.size() - 1];
}

bool Parser::isTypeOf(TokenType type) {
    return getToken()->getType() == type;
}

bool Parser::isValueOf(const std::string& value) {
    return getToken()->getValue() == value;
}

std::shared_ptr<Token> Parser::parseNext(TokenType type) {
    if (!isTypeOf(type)) {
        // TODO(zhengteck): Throw exception
    }
    return getNext();
}

std::shared_ptr<Token> Parser::parseNext(const std::string& value) {
    if (!isValueOf(value)) {
        // TODO(zhengteck): Throw exception
    }
    return getNext();
}
