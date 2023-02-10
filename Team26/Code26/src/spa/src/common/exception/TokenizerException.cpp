#include "TokenizerException.h"

extern const char TokenizerRuntimeExceptionMessage[] = " A run time error occurred with the Tokenizer.";

TokenizerException::TokenizerException() : std::runtime_error(TokenizerRuntimeExceptionMessage) {}

TokenizerException::TokenizerException(const std::string &errorMessage) : std::runtime_error(errorMessage) {}

