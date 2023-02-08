#include "QueryExceptionMessages.h"

const char QueryValidatorDuplicatedSynonymInDeclaration[] =
        "No duplicated synonyms allowed. This synonym has been declared more than once: ";
const char QueryValidatorUndeclaredSelectClauseSynonym[] =
        "Please select a synonym that was in the declaration. This synonym has yet to be declared: ";

const char QueryParserInvalidRelationshipInSelectClause[] =
        " is not a valid relationship, please modify your input. Note that PQL is case-sensitive.";
const char QueryParserInvalidTokenForRelationshipArgument[] =
        "Invalid argument type in relationship clause. Please modify your input.";
extern const char QueryValidatorUndeclaredSuchThatClauseArgument[] =
        "This argument in the relationship clause has yet to be declared: ";
extern const char QueryParserInvalidEndingSemicolon[] =
        "Please remove the semicolon at the end of your Select clause.";
extern const char QueryParserUnexpectedToken[] =
        " Please check your input, unexpected token while parsing: ";
