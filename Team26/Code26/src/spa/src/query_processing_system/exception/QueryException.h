#pragma once
#include <stdexcept>
#include <string>
#include "common/exception/ParserException.h"

extern const std::string ValidationExceptionMessage;
extern const std::string ParserExceptionMessage;
extern const std::string InvalidRelationship;
extern const std::string InvalidArgument;

class QueryValidationException : public ParserException {
 public:
    QueryValidationException() : ParserException(ValidationExceptionMessage) {}
    explicit QueryValidationException(const std::string& errorMessage) : ParserException(errorMessage) {}
};

class QueryInvalidRelationship : public ParserException {
 public:
    QueryInvalidRelationship() : ParserException(InvalidRelationship) {}
    explicit QueryInvalidRelationship(const std::string& errorMessage) : ParserException(errorMessage) {}
};

class QueryParserException : public ParserException {
 public:
    QueryParserException() : ParserException(ParserExceptionMessage) {}
    explicit QueryParserException(const std::string& errorMessage) : ParserException(errorMessage) {}
};

class QueryInvalidRelationshipArguments : public ParserException {
 public:
    QueryInvalidRelationshipArguments() : ParserException(InvalidArgument) {}
    explicit QueryInvalidRelationshipArguments(const std::string& errorMessage) : ParserException(errorMessage) {}
};

class QueryInvalidPatternArgument : public ParserException {
 public:
    QueryInvalidPatternArgument() : ParserException(InvalidArgument) {}
    explicit QueryInvalidPatternArgument(const std::string& errorMessage) : ParserException(errorMessage) {}
};
