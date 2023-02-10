#include "AbstractParser.h"
#include <utility>
#include <string>
#include "common/exception/ParserException.h"
#include "common/exception/ExceptionMessage.h"


AbstractParser::AbstractParser(std::vector<std::shared_ptr<Token>> tokens) : tokens(std::move(tokens)) {}

bool AbstractParser::hasNext() {
    return index < tokens.size() - 1;
}

std::shared_ptr<Token> AbstractParser::getToken() {
    return tokens[index];
}

std::shared_ptr<Token> AbstractParser::getNext() {
    return tokens[index++];
}

std::shared_ptr<Token> AbstractParser::getEOF() {
    return tokens[tokens.size() - 1];
}

bool AbstractParser::isTypeOf(TokenType type) {
    return getToken()->getType() == type;
}

bool AbstractParser::isValueOf(const std::string& value) {
    return getToken()->getValue() == value;
}

std::shared_ptr<Token> AbstractParser::parseNext(TokenType type) {
    if (!isTypeOf(type)) {
        throw ParserException(ParserMismatchTokenTypeExceptionMessage);
    }
    return getNext();
}

std::shared_ptr<Token> AbstractParser::parseNext(const std::string& value) {
    if (!isValueOf(value)) {
        throw ParserException(ParserMismatchTokenValueExceptionMessage + value + "].");
    }
    return getNext();
}
