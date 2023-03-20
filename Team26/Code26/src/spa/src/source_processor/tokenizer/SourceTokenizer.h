#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include <sstream>
#include <string>
#include "common/tokenizer/AbstractTokenizer.h"


class SourceTokenizer : public AbstractTokenizer {
 private:
    bool isValidSpecialChar();
    bool isPossibleLogicalOp();
    bool isValidLogicalOp();

    void readSpecialChar() override;

 public:
    explicit SourceTokenizer(std::istream* stream);

    std::vector<std::shared_ptr<Token>> tokenize() override;
};
