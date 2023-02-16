#pragma once

#include <stdexcept>
#include <string>

#include "QuerySemanticException.h"
#include "QuerySyntaxException.h"

extern const std::string ValidationExceptionMessage;
extern const std::string ParserExceptionMessage;
extern const std::string InvalidRelationship;
extern const std::string InvalidArgument;

class QueryValidationException : public QuerySemanticException {
 public:
    QueryValidationException() : QuerySemanticException(ValidationExceptionMessage) {}
    explicit QueryValidationException(const std::string& errorMessage) : QuerySemanticException(errorMessage) {}
};

class QueryInvalidPatternArgument : public QuerySemanticException {
public:
    QueryInvalidPatternArgument() : QuerySemanticException(InvalidArgument) {}
    explicit QueryInvalidPatternArgument(const std::string& errorMessage) : QuerySemanticException(errorMessage) {}
};

class QueryInvalidRelationshipArguments : public QuerySemanticException {
public:
    QueryInvalidRelationshipArguments() : QuerySemanticException(InvalidArgument) {}
    explicit QueryInvalidRelationshipArguments(const std::string& errorMessage) : QuerySemanticException(errorMessage) {}
};

class QueryInvalidRelationship : public QuerySyntaxException {
 public:
    QueryInvalidRelationship() : QuerySyntaxException(InvalidRelationship) {}
    explicit QueryInvalidRelationship(const std::string& errorMessage) : QuerySyntaxException(errorMessage) {}
};

class QueryParserException : public QuerySyntaxException {
 public:
    QueryParserException() : QuerySyntaxException(ParserExceptionMessage) {}
    explicit QueryParserException(const std::string& errorMessage) : QuerySyntaxException(errorMessage) {}
};
