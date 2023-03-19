#include "SourceProcessorExceptionMessage.h"

extern const char ManagerInvalidInputFile[] = "Invalid input file.";

extern const char TokenizerInvalidLogicalOpExceptionMessage[] = "Invalid logical operation detected. Valid logical "
                                                                "operations includes: \"&&\", \"||\", \">=\", \"<=\", "
                                                                "\"==\", \"!=\".";
extern const char TokenizerSpecialCharExceptionMessage[] = "Invalid special character detected. Valid special "
                                                                  "char includes: \"{\", \"}\", \";\", \"(\", \")\", "
                                                                  "\"=\", \">\", \"<\", \"+\", \"-\", \"*\", \"/\","
                                                                  " \"%\", \"!\".";

extern const char ParserEmptySourceExceptionMessage[] = "Source code contains no procedures. Valid source code is"
                                                        " contained within procedure blocks.";
extern const char ParserEmptyStmtListExceptionMessage[] = "Empty stmt list detected. Valid stmt lists contain at "
                                                          "least one stmt.";
extern const char ParserInvalidStmtStartTokenTypeExceptionMessage[] = "Non-name token at start of statement list"
                                                                      " detected.";
extern const char ParserInvalidStmtStartTokenUnknownExceptionMessage[] = "Invalid token at start of statement"
                                                                         " list detected. Valid tokens include:"
                                                                         " \"read\", \"print\", \"call\", \"if\","
                                                                         "\"while\", or a valid variable name.";
extern const char ParserMissingThenKeywordExceptionMessage[] = "Missing \"then\" keyword in if-then-else clause.";
extern const char ParserMissingElseKeywordExceptionMessage[] = "Missing \"else\" keyword in if-then-else clause.";
extern const char ParserInvalidCondExprExceptionMessage[] = "Invalid cond_expr format detected. A valid cond_expr "
                                                            "expression is of the format: rel_expr | '!' '(' "
                                                            "cond_expr ')' | '(' cond_expr ')' '&&' '(' cond_expr "
                                                            "')' | '(' cond_expr ')' '||' '(' cond_expr ')'";

extern const char BaseExtractRuntimeExceptionMessage[] =
        "A run time error occurred with the Base Extractor.";

extern const char BaseExtractorEmptyStatementListExceptionMessage[] =
        "Empty Statement list detected.";
extern const char BaseExtractorEmptyProcedureListExceptionMessage[] =
        "Empty Procedure list detected.";

extern const char RelationshipExtractorCyclicCallsExceptionMessage[] =
        "Cyclic call detected. It is not allowed in a SIMPLE program.";

extern const char RelationshipExtractorSelfCallsExceptionMessage[] =
        "Self call detected. It is not considered as a cyclic call and not allowed in SIMPLE program.";

extern const char RelationshipExtractorNonExistentExceptionMessage[] =
        "Call statement is calling a non-existent procedure.";
