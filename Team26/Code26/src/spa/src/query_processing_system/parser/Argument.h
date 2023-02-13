#pragma once

#include <map>
#include <string>
#include "DesignEntity.h"

/**
 * Types of arguments in clauses
 * Synonyms: Declarations
 * Number: Statement numbers
 * Wildcard: _
 * StringExpression: String within a set of inverted commas
 */
enum class ArgumentType {
    SYNONYM = 0,
    NUMBER = 1,
    WILDCARD = 2,
    CHARACTERSTRING = 3
};

/**
 * Follows | FollowsT | Parent | ParentT : stmtRef, stmtRef
 * UsesS | ModifiesS : stmtRef, entRef
 * UsesP | ModifiesP : entRef, entRef
 * stmtRef = Synonym, Number, Wildcard
 * entRef = Synonym, Number, Character String
 */
using ArgTypeIndex = std::unordered_set<unsigned int>;
static ArgTypeIndex stmtRef{0, 1, 2};
static ArgTypeIndex entRef{0, 1, 3};

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

    int getArgumentTypeIndex(ArgumentType);
};
