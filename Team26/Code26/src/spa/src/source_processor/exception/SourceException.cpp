#include "SourceException.h"

SourceParserException::SourceParserException() = default;

SourceParserException::SourceParserException(const std::string &errorMessage) : ParserException(errorMessage) {}

SourceTokenizerException::SourceTokenizerException() = default;

SourceTokenizerException::SourceTokenizerException(const std::string &errorMessage) : TokenizerException(errorMessage) {
}

SourceExtractorException::SourceExtractorException() : std::runtime_error(BaseExtractRuntimeExceptionMessage) {
}

SourceExtractorException::SourceExtractorException(const std::string &errorMessage) : runtime_error(errorMessage) {
}

