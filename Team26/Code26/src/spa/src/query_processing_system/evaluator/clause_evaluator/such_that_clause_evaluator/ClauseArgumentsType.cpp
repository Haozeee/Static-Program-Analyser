#include "ClauseArgumentsType.h"

ClauseArgumentTypes getClauseArgumentType(ArgumentType leftArg, ArgumentType rightArg) {
    if (leftArg == ArgumentType::NUMBER && rightArg == ArgumentType::NUMBER) {
        return ClauseArgumentTypes::NUMBER_NUMBER;
    } else if (leftArg == ArgumentType::SYNONYM && rightArg == ArgumentType::NUMBER) {
        return ClauseArgumentTypes::SYNONYM_NUMBER;
    } else if (leftArg == ArgumentType::NUMBER && rightArg == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::NUMBER_SYNONYM;
    } else if (leftArg == ArgumentType::SYNONYM && rightArg == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::SYNONYM_SYNONYM;
    } else if (leftArg == ArgumentType::NUMBER && rightArg == ArgumentType::CHARACTERSTRING) {
        return ClauseArgumentTypes::NUMBER_STRING;
    } else if (leftArg == ArgumentType::SYNONYM && rightArg == ArgumentType::CHARACTERSTRING) {
        return ClauseArgumentTypes::SYNONYM_STRING;
    } else if (leftArg == ArgumentType::SYNONYM && rightArg == ArgumentType::WILDCARD) {
        return ClauseArgumentTypes::SYNONYM_WILDCARD;
    } else if (leftArg == ArgumentType::WILDCARD && rightArg == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::WILDCARD_SYNONYM;
    } else if (leftArg == ArgumentType::WILDCARD && rightArg == ArgumentType::CHARACTERSTRING) {
        return ClauseArgumentTypes::WILDCARD_STRING;
    } else if (leftArg == ArgumentType::WILDCARD && rightArg == ArgumentType::NUMBER) {
        return ClauseArgumentTypes::WILDCARD_NUMBER;
    } else if (leftArg == ArgumentType::NUMBER && rightArg == ArgumentType::WILDCARD) {
        return ClauseArgumentTypes::NUMBER_WILDCARD;
    } else if (leftArg == ArgumentType::WILDCARD && rightArg == ArgumentType::WILDCARD) {
        return ClauseArgumentTypes::WILDCARD_WILDCARD;
    } else {
        return ClauseArgumentTypes::NONE;
    }
}
