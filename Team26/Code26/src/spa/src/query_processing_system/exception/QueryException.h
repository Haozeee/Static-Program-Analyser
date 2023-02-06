#pragma once

#include <stdexcept>
#include <string>

extern const std::string ValidationException;

class QueryValidationException : public std::runtime_error {
 public:
    QueryValidationException() : std::runtime_error(ValidationException) {}
    explicit QueryValidationException(const std::string& errorMessage) : std::runtime_error(errorMessage) {}
};
