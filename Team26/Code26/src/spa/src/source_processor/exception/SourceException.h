#pragma once

#include <string>
#include "common/exception/ParserException.h"
#include "common/exception/TokenizerException.h"

class SourceTokenizerException : public TokenizerException {
 public:
    SourceTokenizerException();
    explicit SourceTokenizerException(const std::string& errorMessage);
};

class SourceParserException : public ParserException {
 public:
    SourceParserException();
    explicit SourceParserException(const std::string& errorMessage);
};

