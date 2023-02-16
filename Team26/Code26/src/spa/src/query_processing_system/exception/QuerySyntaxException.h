#pragma once

#include "common/exception/ParserException.h"

extern const std::string syntaxExceptionMessage;

class QuerySyntaxException : public ParserException {
public:
    QuerySyntaxException() : ParserException(syntaxExceptionMessage) {}
    explicit QuerySyntaxException(const std::string& errorMessage) : ParserException(errorMessage) {}
};
