#include "SourceTokenizer.h"

SourceTokenizer::SourceTokenizer(std::istream* stream) : Tokenizer(stream) {}

std::vector<std::shared_ptr<Token>> SourceTokenizer::tokenize() {
    // TODO(laugingkid-sg): Implement SP tokenizer
    std::vector<std::shared_ptr<Token>>  tokenList;
    return tokenList;
}
