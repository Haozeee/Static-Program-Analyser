#include "AbstractTokenizer.h"
#include <sstream>
#include <memory>
#include "common/exception/TokenizerException.h"
#include "common/exception/ExceptionMessage.h"

AbstractTokenizer::AbstractTokenizer(std::istream* stream) : istream(stream) {}

AbstractTokenizer::AbstractTokenizer(const std::string& query) {
    auto* inputStringStream = new std::stringstream(query);
    istream = inputStringStream;
}

char AbstractTokenizer::nextChar() {
    return static_cast<char>(istream->get());
}

char AbstractTokenizer::peekChar() {
    return static_cast<char>(istream->peek());
}

std::string AbstractTokenizer::getCurrentToken() {
    return currentToken;
}

void AbstractTokenizer::readInteger() {
    char c = peekChar();
    while (isdigit(c)) {
        currentToken += nextChar();
        c = peekChar();
    }

    if (hasLeadingZero()) {
        throw TokenizerException(TokenizerLeadingZeroExceptionMessage);
    }
}

bool AbstractTokenizer::hasLeadingZero() {
    return currentToken.size() > 1 && currentToken.at(0) == '0';
}

void AbstractTokenizer::readName() {
    char c = peekChar();
    while (isalnum(c)) {
        currentToken += nextChar();
        c = peekChar();
    }
}

void AbstractTokenizer::addToken(const std::shared_ptr<Token>& token) {
    tokens.push_back(token);
}

std::vector<std::shared_ptr<Token>> AbstractTokenizer::getTokens() {
    return tokens;
}
