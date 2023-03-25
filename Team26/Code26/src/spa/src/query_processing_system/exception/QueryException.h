#pragma once

#include <stdexcept>
#include <string>

#include "QuerySemanticException.h"
#include "QuerySyntaxException.h"

class QueryParserException : public QuerySyntaxException {
 public:
    explicit QueryParserException(const std::string& errorMessage) : QuerySyntaxException(errorMessage) {}
};

class QueryTokenizerException : public QuerySyntaxException {
 public:
    explicit QueryTokenizerException(const std::string& errorMessage) : QuerySyntaxException(errorMessage) {}
};

class SyntaxException : public QuerySyntaxException {
 public:
    explicit SyntaxException(const std::string& errorMessage) : QuerySyntaxException(errorMessage) {}
};

class SemanticException : public QuerySemanticException {
 public:
    explicit SemanticException(const std::string& errorMessage) : QuerySemanticException(errorMessage) {}
};
