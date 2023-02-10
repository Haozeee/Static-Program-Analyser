#pragma once

#include <vector>
#include <memory>
#include "common/tokenizer/AbstractTokenizer.h"


class Tokenizer : public AbstractTokenizer {
 private:
    bool isValidSpecialChar();
    bool isPossibleLogicalOp();
    bool isValidLogicalOp();

    void readSpecialChar() override;

 public:
    explicit Tokenizer(std::istream* stream);

    std::vector<std::shared_ptr<Token>> tokenize() override;
};
