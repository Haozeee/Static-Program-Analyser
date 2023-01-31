#pragma once

#include <vector>
#include <memory>
#include "common/Tokenizer.h"


class QueryTokenizer : public Tokenizer {
public:
    explicit QueryTokenizer(std::string query);

    std::vector<std::shared_ptr<Token>> tokenize();
};
