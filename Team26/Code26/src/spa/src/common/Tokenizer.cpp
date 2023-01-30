#include "Tokenizer.h"
#include <sstream>

Tokenizer::Tokenizer(std::istream* stream) : istream(stream) {}

Tokenizer::Tokenizer(const std::string& query) {
    auto* inputStringStream = new std::stringstream(query);
    istream = inputStringStream;
}

char Tokenizer::nextChar() {
    return (char) istream->get();
}

char Tokenizer::peekChar() {
    return (char) istream->peek();
}

std::string Tokenizer::getCurrentToken() {
    return this->currentToken;
}

void Tokenizer::readInteger() {
    char c = peekChar();
    while (isdigit(c)) {
        currentToken += nextChar();
        c = peekChar();
    }

    if (hasLeadingZero()) {
        // TODO: Throw exception.
    }
}

bool Tokenizer::hasLeadingZero() {
    return currentToken.size() > 1 && currentToken.at(0) == '0';
}

void Tokenizer::readName() {
    char c = peekChar();
    while (isalnum(c)) {
        currentToken += nextChar();
        c = peekChar();
    }
}

void Tokenizer::addToken(std::shared_ptr<Token> token) {
    tokens.push_back(token);
}

std::vector<std::shared_ptr<Token>> Tokenizer::getTokens() {
    return this->tokens;
}