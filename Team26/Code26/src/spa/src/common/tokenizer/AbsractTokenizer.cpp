#include "AbsractTokenizer.h"
#include <sstream>
#include <memory>

AbsractTokenizer::AbsractTokenizer(std::istream* stream) : istream(stream) {}

AbsractTokenizer::AbsractTokenizer(const std::string& query) {
    auto* inputStringStream = new std::stringstream(query);
    istream = inputStringStream;
}

char AbsractTokenizer::nextChar() {
    return static_cast<char>(istream->get());
}

char AbsractTokenizer::peekChar() {
    return static_cast<char>(istream->peek());
}

std::string AbsractTokenizer::getCurrentToken() {
    return currentToken;
}

void AbsractTokenizer::readInteger() {
    char c = peekChar();
    while (isdigit(c)) {
        currentToken += nextChar();
        c = peekChar();
    }

    if (hasLeadingZero()) {
        // TODO(laughingkid-sg): Throw exception.
    }
}

bool AbsractTokenizer::hasLeadingZero() {
    return currentToken.size() > 1 && currentToken.at(0) == '0';
}

void AbsractTokenizer::readName() {
    char c = peekChar();
    while (isalnum(c)) {
        currentToken += nextChar();
        c = peekChar();
    }
}

void AbsractTokenizer::addToken(std::shared_ptr<Token> token) {
    tokens.push_back(token);
}

std::vector<std::shared_ptr<Token>> AbsractTokenizer::getTokens() {
    return tokens;
}
