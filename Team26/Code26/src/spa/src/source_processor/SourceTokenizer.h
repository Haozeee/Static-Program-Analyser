#pragma once

#include <vector>
#include <memory>
#include "common/tokenizer/AbsractTokenizer.h"


class SourceTokenizer : public AbsractTokenizer {
 private:
    bool isValidSpecialChar();
    bool isPossibleLogicalOp();
    bool isValidLogicalOp();

    void readSpecialChar() override;

 public:
    explicit SourceTokenizer(std::istream* stream);

    std::vector<std::shared_ptr<Token>> tokenize() override;
};
