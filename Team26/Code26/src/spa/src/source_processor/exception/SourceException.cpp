#include "SourceException.h"

SourceParserException::SourceParserException() = default;

SourceParserException::SourceParserException(const std::string &errorMessage) : ParserException(errorMessage) {}

SourceTokenizerException::SourceTokenizerException() = default;

SourceTokenizerException::SourceTokenizerException(const std::string &errorMessage) : TokenizerException(errorMessage) {
}
