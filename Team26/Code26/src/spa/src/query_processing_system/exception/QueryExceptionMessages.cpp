#include "QueryExceptionMessages.h"

const char QueryValidatorDuplicatedSynonymInDeclaration[] =
        "No duplicated synonyms allowed. This synonym has been declared more than once: ";
const char QueryValidatorSynonymInSelectClauseNotDeclared[] =
        "Please select a synonym that was in the declaration. This synonym has yet to be declared: ";

const char QueryInvalidRelationshipInSelectClause[] =
        " is not a valid relationship. Please modify your input.";