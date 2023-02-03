#pragma once
#include <string>

/**
 * Types of arguments in clauses
 * Synonyms: Declarations
 * Number: Statement numbers
 */
enum class ArgumentType {
    SYNONYM,
    NUMBER
};

class Argument {
private:
    ArgumentType argumentType;
    std::string value;

public:
    Argument(ArgumentType type, std::string value);

    std::string getValue();

    ArgumentType getArgumentType();
};
