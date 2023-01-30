#include "SourceTokenizer.h"

SourceTokenizer::SourceTokenizer(std::istream* stream) : Tokenizer(stream) {}

std::vector<std::shared_ptr<Token>> SourceTokenizer::tokenize() {
    // TODO: Implement SP tokenizer
    std::vector<std::shared_ptr<Token>>  tokenList;
    return tokenList;
}