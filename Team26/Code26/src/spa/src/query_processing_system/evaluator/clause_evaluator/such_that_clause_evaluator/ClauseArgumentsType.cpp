#include "ClauseArgumentsType.h"

bool isValueArgumentType(ArgumentType arg) {
    return arg == ArgumentType::CHARACTERSTRING || arg == ArgumentType::NUMBER;
}
ClauseArgumentTypes getClauseArgumentType(ArgumentType leftArg, ArgumentType rightArg) {
    if (isValueArgumentType(leftArg) && isValueArgumentType(rightArg)) {
        return ClauseArgumentTypes::VALUE_VALUE;
    } else if (leftArg == ArgumentType::SYNONYM && isValueArgumentType(rightArg)) {
        return ClauseArgumentTypes::SYNONYM_VALUE;
    } else if (isValueArgumentType(leftArg) && rightArg == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::VALUE_SYNONYM;
    } else if (leftArg == ArgumentType::SYNONYM && rightArg == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::SYNONYM_SYNONYM;
    } else if (leftArg == ArgumentType::SYNONYM && rightArg == ArgumentType::WILDCARD) {
        return ClauseArgumentTypes::SYNONYM_WILDCARD;
    } else if (leftArg == ArgumentType::WILDCARD && rightArg == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::WILDCARD_SYNONYM;
    } else if (leftArg == ArgumentType::WILDCARD && isValueArgumentType(rightArg)) {
        return ClauseArgumentTypes::WILDCARD_VALUE;
    } else if (isValueArgumentType(leftArg) && rightArg == ArgumentType::WILDCARD) {
        return ClauseArgumentTypes::VALUE_WILDCARD;
    } else if (leftArg == ArgumentType::WILDCARD && rightArg == ArgumentType::WILDCARD) {
        return ClauseArgumentTypes::WILDCARD_WILDCARD;
    } else {
        return ClauseArgumentTypes::NONE;
    }
}
