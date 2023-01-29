#pragma once

#include "common/tokens/Token.h"

#include <vector>
#include <string>


class Tokenizer {

protected:
    std::istream* istream;
    std::string curr;
    std::vector<Token*> tokens;

    char nextChar();
    char peekChar();
    void nextInteger();
    void nextName();

    void addToken(Token* token);

public:

    // Constructor for SP
    explicit Tokenizer(std::istream* stream);

    // Constructor for QPS
    explicit Tokenizer(std::string query);

    std::string getCurrent();
    std::vector<Token*> getTokens();

    // Implementation for tokenization
    virtual std::vector<Token*> tokenize() = 0;
};
