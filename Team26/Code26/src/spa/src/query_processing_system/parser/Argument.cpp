#include "Argument.h"
#include <utility>

Argument::Argument(ArgumentType type, std::string value)
    : argumentType(type), value(std::move(value)) {}

ArgumentType Argument::getArgumentType() {
    return argumentType;
}

std::string Argument::getValue() {
    return value;
}
