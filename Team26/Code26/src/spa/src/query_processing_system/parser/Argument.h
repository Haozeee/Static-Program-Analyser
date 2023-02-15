#pragma once

#include <map>
#include <string>
#include <unordered_set>

#include "DesignEntity.h"

/**
 * Types of arguments in clauses
 * Synonyms: Declarations
 * Number: Statement numbers
 * Wildcard: _
 * StringExpression: String within a set of inverted commas
 */
enum class ArgumentType {
    SYNONYM,
    NUMBER,
    WILDCARD,
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
     * The value of the argument.
     */
    std::string value;

    /**
     * The design entity of the argument.
     */
    DesignEntity designEntity;

 public:
    Argument(ArgumentType type, std::string value, DesignEntity designEntity);

    std::string getValue();

    ArgumentType getArgumentType();

    DesignEntity getDesignEntity();
};
