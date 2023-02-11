#include "QueryExceptionMessages.h"

const char QueryValidatorDuplicatedSynonymInDeclaration[] =
        "No duplicated synonyms allowed. This synonym has been declared more than once: ";
const char QueryValidatorUndeclaredSelectClauseSynonym[] =
        "Please select a synonym that was in the declaration. This synonym has yet to be declared: ";
const char QueryValidatorUndeclaredSuchThatClauseArgument[] =
        "This argument in the relationship clause has yet to be declared: ";
const char QueryValidatorInvalidAssignPatternSynonym[] =
        " needs to be declared as an assign synonym to be used in an assign pattern clause.";

const char QueryParserInvalidRelationshipInSelectClause[] =
        " is not a valid relationship, please modify your input. Note that PQL is case-sensitive.";
const char QueryParserInvalidModifiesOrUsesRelationshipInSelectClause[] =
        " relationship has an invalid first argument.";
const char QueryParserInvalidTokenForRelationshipArgument[] =
        " is an invalid argument type in the relationship clause. Please modify your input.";
const char QueryParserInvalidEndingSemicolon[] =
        "Please remove the semicolon at the end of your Select clause.";
const char QueryParserUnexpectedToken[] =
        "Please check your input, unexpected token while parsing: ";
