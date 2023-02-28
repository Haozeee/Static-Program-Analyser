#pragma once
#include "query_processing_system/parser/Argument.h"

enum class ClauseArgumentTypes {
    VALUE_VALUE,
    SYNONYM_VALUE,
    VALUE_SYNONYM,
    SYNONYM_SYNONYM,
    WILDCARD_VALUE,
    VALUE_WILDCARD,
    SYNONYM_WILDCARD,
    WILDCARD_SYNONYM,
    WILDCARD_WILDCARD,
    NONE
};

bool isValueArgumentType(ArgumentType arg);

ClauseArgumentTypes getClauseArgumentType(ArgumentType leftArg, ArgumentType rightArg);
