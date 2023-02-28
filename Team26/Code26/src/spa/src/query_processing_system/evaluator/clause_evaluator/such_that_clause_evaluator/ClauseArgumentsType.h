#pragma once
#include "query_processing_system/parser/Argument.h"

enum class ClauseArgumentTypes {
    NUMBER_NUMBER,
    SYNONYM_NUMBER,
    NUMBER_SYNONYM,
    SYNONYM_SYNONYM,
    SYNONYM_STRING,
    NUMBER_STRING,
    WILDCARD_NUMBER,
    NUMBER_WILDCARD,
    SYNONYM_WILDCARD,
    WILDCARD_SYNONYM,
    WILDCARD_WILDCARD,
    WILDCARD_STRING,
    STRING_STRING,
    STRING_SYNONYM,
    STRING_WILDCARD,
    NONE
};

ClauseArgumentTypes getClauseArgumentType(ArgumentType leftArg, ArgumentType rightArg);
