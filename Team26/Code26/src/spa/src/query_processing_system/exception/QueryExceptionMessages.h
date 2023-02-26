#pragma once

#include <string>

/**
 * Semantic Errors
 */
extern const char QueryValidatorDuplicatedSynonymInDeclaration[];
extern const char QueryValidatorUndeclaredSelectClauseSynonym[];
extern const char QueryValidatorUndeclaredSuchThatClauseArgument[];
extern const char QueryValidatorInvalidFirstArgumentTypeInRelation[];
extern const char QueryValidatorInvalidSecondArgumentTypeInRelation[];
extern const char QueryValidatorInvalidFirstDesignEntityInRelation[];
extern const char QueryValidatorInvalidSecondDesignEntityInRelation[];
extern const char QueryValidatorInvalidModifiesOrUsesRelationshipInSelectClause[];
extern const char QueryInvalidCreatePatternArgument[];
extern const char QueryInvalidNumberOfPatternArguments[];

/**
 * Syntax Errors
 */
extern const char QueryParserInvalidWildcardInSelectClause[];
extern const char QueryParserInvalidRelationshipInSelectClause[];
extern const char QueryParserInvalidTokenForRelationshipArgument[];
extern const char QueryParserInvalidEndingSemicolon[];
extern const char QueryParserUnexpectedToken[];
extern const char QueryParserUnbalancedStringExpression[];
extern const char QueryParserPatternClauseNonWildcardArgument[];
extern const char QueryValidatorIfWhilePatternRightArgWildcard[];
