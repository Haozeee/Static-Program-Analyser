#include "ParserException.h"

extern const char ParserRuntimeExceptionMessage[] = " A run time error occurred with the Parser.";

ParserException::ParserException() : std::runtime_error(ParserRuntimeExceptionMessage) {}
ParserException::ParserException(const std::string &errorMessage) : std::runtime_error(errorMessage) {}
