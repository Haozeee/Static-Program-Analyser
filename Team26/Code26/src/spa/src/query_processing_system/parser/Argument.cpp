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

int Argument::getArgumentTypeIndex(ArgumentType argType) {
    switch (argType) {
        case (ArgumentType::SYNONYM):
            return 0;
        case (ArgumentType::NUMBER):
            return 1;
        case (ArgumentType::WILDCARD):
            return 2;
        case (ArgumentType::CHARACTERSTRING):
            return 3;
        default:
            return -1;
    }
}
