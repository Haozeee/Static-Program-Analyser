#include "QueryExceptionMessages.h"

/**
 * Semantic Errors
 */
const char QueryValidatorDuplicatedSynonymInDeclaration[] =
        "No duplicated synonyms allowed. This synonym has been declared more than once: ";
const char QueryValidatorUndeclaredSelectClauseSynonym[] =
        "Please select a synonym that was in the declaration. This synonym has yet to be declared: ";
const char QueryValidatorUndeclaredSuchThatClauseArgument[] =
        "This argument in the relationship clause has yet to be declared: ";
const char QueryValidatorInvalidFirstArgumentTypeInRelation[] =
        " is not a valid first argument type for the given relation. ";
const char QueryValidatorInvalidSecondArgumentTypeInRelation[] =
        " is not a valid second argument type for the given relation.";
const char QueryValidatorInvalidFirstDesignEntityInRelation1[] =
        "The synonym ";
const char QueryValidatorInvalidFirstDesignEntityInRelation2[] =
        " of design entity ";
const char QueryValidatorInvalidFirstDesignEntityInRelation[] =
        " is an invalid first argument for the given relation.";
const char QueryValidatorInvalidSecondDesignEntityInRelation[] =
        " is not a valid second argument for the given relation.";
const char QueryValidatorInvalidModifiesOrUsesRelationshipInSelectClause[] =
        " relationship was not created as the first argument cannot be identified. Note that wildcards are invalid.";
const char QueryInvalidCreatePatternArgument[] =
        " needs to be declared as an assign synonym to be used in an assign pattern clause.";
const char QueryInvalidStartOrEndSpecialCharInStringExpression[] =
        "Cannot start/end string expression with operator";

/**
 * Syntax Errors
 */
const char QueryParserInvalidWildcardInSelectClause[] =
        "Not allowed to select a wildcard.";
const char QueryParserInvalidRelationshipInSelectClause[] =
        " is not a valid relationship, please modify your input. Note that PQL is case-sensitive.";
const char QueryParserInvalidTokenForRelationshipArgument[] =
        " is an invalid argument type in the relationship clause. Please modify your input.";
const char QueryParserInvalidEndingSemicolon[] =
        "Please remove the semicolon at the end of your Select clause.";
const char QueryParserUnexpectedToken[] =
        "Please check your input, unexpected token while parsing: ";

