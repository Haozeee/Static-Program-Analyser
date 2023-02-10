#pragma once
#include <stdexcept>
#include <string>
#include "common/exception/ExceptionMessage.h"

extern const char ParserRuntimeExceptionMessage[];

class ParserException : public std::runtime_error {
 public:
    ParserException();
    explicit ParserException(const std::string& errorMessage);
};
