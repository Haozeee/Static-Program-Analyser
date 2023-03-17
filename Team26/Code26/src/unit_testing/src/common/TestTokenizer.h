#pragma once

#include <memory>
#include <string>
#include <vector>
#include "catch.hpp"
#include "common/tokenizer/AbstractTokenizer.h"

class TestTokenizer : public AbstractTokenizer {
 public:
    explicit TestTokenizer(std::istream* stream);
    explicit TestTokenizer(const std::string& query);

    char nextChar();
    char peekChar();
    void readName();
    void readInteger();
    std::string getCurrentToken();
    std::vector<std::shared_ptr<Token>> tokenize() override;
    void readSpecialChar() override;
};
