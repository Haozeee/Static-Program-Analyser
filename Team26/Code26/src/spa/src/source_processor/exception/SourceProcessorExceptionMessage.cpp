#include "SourceProcessorExceptionMessage.h"

extern const char TokenizerInvalidLogicalOpExceptionMessage[] = "Invalid logical operation detected. Valid logical "
                                                                "operations includes: \"&&\", \"||\", \">=\", \"<=\", "
                                                                "\"==\", \"!=\".";
extern const char TokenizerSpecialCharExceptionMessage[] = "Invalid special character detected. Valid special "
                                                                  "char includes: \"{\", \"}\", \";\", \"(\", \")\", "
                                                                  "\"=\", \">\", \"<\", \"+\", \"-\", \"*\", \"/\","
                                                                  " \"%\", \"!\".";

extern const char ParserEmptySourceExceptionMessage[] = "Source code contains no procedures. Valid source code is"
                                                        " contained within procedure blocks.";
extern const char ParserInvalidStmtStartTokenTypeExceptionMessage[] = "Non-name token at start of statement list"
                                                                      " detected.";
extern const char ParserInvalidStmtStartTokenUnknownExceptionMessage[] = "Invalid token at start of statement"
                                                                         " list detected. Valid tokens include:"
                                                                         " \"read\", \"print\", \"call\", \"if\","
                                                                         "\"while\", or a valid variable name.";
extern const char ParserInvalidFactorExceptionMessage[] = "Invalid factor token detected. Valid factor tokens"
                                                          " include: integer, variable name.";
extern const char ParserMissingThenKeywordExceptionMessage[] = "Missing \"then\" keyword in if-then-else clause.";
extern const char ParserMissingElseKeywordExceptionMessage[] = "Missing \"else\" keyword in if-then-else clause.";
extern const char ParserInvalidBinaryCondExprFormatExceptionMessage[] = "Invalid binary conditional expression"
                                                                        " clause detected. A valid conditional "
                                                                        " expression is of the format: (cond_expr)"
                                                                        " && (cond_expr) or (cond_expr) || (cond_expr)";
extern const char ParserMissingRelOperatorExceptionMessage[] = "Missing comparison operator in rel_factor detected."
                                                               "Valid comparison operators include: \">\", \"<\","
                                                               " \">=\", \"<=\", \"==\", \"!=\".";
extern const char ParserInvalidExprFormatExceptionMessage[] = "Invalid expr clause detected. A valid expr clause is"
                                                              " of the format: expr '+' term | expr '-' term | term"
                                                              " with term: term '*' factor | term '/' factor | term"
                                                              " '%' factor | factor and factor: var_name | "
                                                              "const_value | '(' expr ')'";
extern const char ParserInvalidOpExceptionMessage[] = "Invalid attempt to parse non-operator token as an operator"
                                                      " detected. Valid operators include: \"+\", \"-\", \"*\", \"/\","
                                                      " \"%\".";
extern const char ParserInvalidTermFormatExceptionMessage[] = "Invalid term clause detected. A valid term clause is"
                                                              " of the format: term: term '*' factor | term '/' "
                                                              "factor | term '%' factor | factor with factor: "
                                                              "var_name | const_value | '(' expr ')' and expr: "
                                                              "expr '+' term | expr '-' term | term";
extern const char ParserInvalidFactorLengthExceptionMessage[] = "Invalid attempt to parse multi-token clause as factor "
                                                                "deteched. Valid factor clauses include: 1 name token,"
                                                                " 1 integer token";

extern const char BaseExtractRuntimeExceptionMessage[] =
        "A run time error occurred with the Base Extractor.";

extern const char BaseExtractorEmptyStatementListExceptionMessage[] =
        "Empty Statement list detected.";
extern const char BaseExtractorEmptyProcedureListExceptionMessage[] =
        "Empty Procedure list detected.";
