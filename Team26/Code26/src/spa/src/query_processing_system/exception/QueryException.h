#pragma once

#include <stdexcept>
#include <string>

extern const std::string ValidationException;
extern const std::string InvalidRelationship;

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
