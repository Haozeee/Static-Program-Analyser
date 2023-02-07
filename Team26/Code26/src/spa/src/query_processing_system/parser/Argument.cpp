#include "Argument.h"
#include <utility>

Argument::Argument(ArgumentType type, std::string value, DesignEntity de)
    : argumentType(type), value(std::move(value)), designEntity(de) {}

ArgumentType Argument::getArgumentType() {
    return argumentType;
}

std::string Argument::getValue() {
    return value;
}

DesignEntity Argument::getDesignEntity() {
    return designEntity;
}
