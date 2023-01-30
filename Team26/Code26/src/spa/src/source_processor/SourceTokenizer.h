#pragma once

#include "common/Tokenizer.h"
class SourceTokenizer : public Tokenizer {

 public:
    SourceTokenizer(std::istream* stream);

    std::vector<Token*> tokenize();
};
