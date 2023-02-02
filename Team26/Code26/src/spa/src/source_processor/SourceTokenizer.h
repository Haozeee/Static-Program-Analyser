#pragma once

#include <vector>
#include <memory>
#include "common/Tokenizer.h"


class SourceTokenizer : public Tokenizer {
 private:
    bool isValidSpecialChar();
    bool isPossibleLogicalOp();
    bool isValidLogicalOp();

    void readSpecialChar() override;

 public:
    explicit SourceTokenizer(std::istream* stream);

    std::vector<std::shared_ptr<Token>> tokenize() override;
};
