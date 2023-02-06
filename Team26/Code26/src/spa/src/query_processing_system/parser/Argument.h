#pragma once
#include <string>

/**
 * Types of arguments in clauses
 * Synonyms: Declarations
 * Number: Statement numbers
 * Wildcard: _
 * CharacterString: String within a set of inverted commas
 */
enum class ArgumentType {
    SYNONYM,
    WILDCARD,
    NUMBER,
    CHARACTERSTRING
};

/**
 * Stores an argument of a query clause.
 */
class Argument {
 private:
    /**
     * The type of the argument.
     */
    ArgumentType argumentType;
    /**
     * The value of the argument
     */
    std::string value;

 public:
    Argument(ArgumentType type, std::string value);

    std::string getValue();

    ArgumentType getArgumentType();
};
