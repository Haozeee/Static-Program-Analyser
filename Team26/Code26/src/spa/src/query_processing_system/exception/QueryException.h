#pragma once

#include <stdexcept>
#include <string>

extern const std::string ValidationException;
extern const std::string InvalidRelationship;
extern const std::string InvalidArgument;

class QueryValidationException : public std::runtime_error {
 public:
    QueryValidationException() : std::runtime_error(ValidationException) {}
    explicit QueryValidationException(const std::string& errorMessage) : std::runtime_error(errorMessage) {}
};

class QueryInvalidRelationship : public std::runtime_error {
 public:
    QueryInvalidRelationship() : std::runtime_error(InvalidRelationship) {}
    explicit QueryInvalidRelationship(const std::string& errorMessage) : std::runtime_error(errorMessage) {}
};

class QueryParserException : public std::runtime_error {
 public:
    QueryParserException() : std::runtime_error(InvalidArgument) {}
    explicit QueryParserException(const std::string& errorMessage) : std::runtime_error(errorMessage) {}
};

class QueryInvalidRelationshipArguments : public std::runtime_error {
 public:
    QueryInvalidRelationshipArguments() : std::runtime_error(InvalidArgument) {}
    explicit QueryInvalidRelationshipArguments(const std::string& errorMessage) : std::runtime_error(errorMessage) {}
};
