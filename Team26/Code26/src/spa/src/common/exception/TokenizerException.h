#pragma once
#include <stdexcept>
#include <string>
#include "common/exception/ExceptionMessage.h"

extern const char TokenizerRuntimeExceptionMessage[];

class TokenizerException : public std::runtime_error {
public:
    TokenizerException();
    explicit TokenizerException(const std::string& errorMessage);
};
