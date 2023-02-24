#include "ExceptionMessage.h"

extern const char TokenizerLeadingZeroExceptionMessage[] = "Leading zeros detected. Constants are sequence of digits "
                                                "with no leading zero.";
extern const char ParserMismatchTokenTypeExceptionMessage[] = "Mismatch token type detected in parser.";
extern const char ParserMismatchTokenValueExceptionMessage[] = "Mismatch token type detected in parser. Token should "
                                                               "not be value of [";

extern const char ParserShuntingYardParserUnknownOperatorExceptionMessage[] =
        R"lit(Invalid operator detected. Only these operators are supported "+", "-", "*", "/", "%", "(" , ").")lit";
extern const char ParserShuntingYardParserInvalidExpressionExceptionMessage[] = "Invalid expression detected.";

