#include "Tokenizer.h"
#include <sstream>

Tokenizer::Tokenizer(std::istream* stream) : istream(stream) {}

Tokenizer::Tokenizer(std::string query) {
    std::stringstream* iss = new std::stringstream(query);
    istream = iss;
}

char Tokenizer::nextChar() {
    return istream->get();
}

char Tokenizer::peekChar() {
    return istream->peek();
}

std::string Tokenizer::getCurrent() {
    return this->curr;
}

void Tokenizer::nextInteger() {
    char c = peekChar();
    while (isdigit(c)) {
        curr += nextChar();
        c = peekChar();
    }
}

void Tokenizer::nextName() {
    char c = peekChar();
    while (isalnum(c)) {
        curr += nextChar();
        c = peekChar();
    }
}

void Tokenizer::addToken(Token* token) {
    tokens.push_back(token);
}

std::vector<Token*> Tokenizer::getTokens() {
    return this->tokens;
}