#pragma once

#include <string>
#include "common/exception/ParserException.h"

extern const std::string semanticExceptionMessage;

class QuerySemanticException : public ParserException {
 public:
    QuerySemanticException() : ParserException(semanticExceptionMessage) {}
    explicit QuerySemanticException(const std::string& errorMessage) : ParserException(errorMessage) {}
};
