#pragma once
#include <string>
#include <ostream>
#include <unordered_map>
#include <unordered_set>

enum class DesignEntity {
    STMT,
    VARIABLE,
    PROCEDURE,
    ASSIGN,
    READ,
    PRINT,
    CALL,
    WHILE,
    IF,
    CONSTANT,
    NONE
};

/**
 * Based on Basic Design Extractions:
 * Follows | FollowsT | Parent | ParentT : Relationship between Statements
 * UsesS | ModifiesS : Relationship between Statement and Variable
 * UsesP | ModifiesP : Relationship between Procedure and Variable
 */
static std::unordered_set<DesignEntity> allStatements = std::unordered_set<DesignEntity>{
    DesignEntity::STMT,
    DesignEntity::READ,
    DesignEntity::PRINT,
    DesignEntity::ASSIGN,
    DesignEntity::CALL,
    DesignEntity::WHILE,
    DesignEntity::IF
};

static std::unordered_set<DesignEntity> procedureOnly = std::unordered_set<DesignEntity>({DesignEntity::PROCEDURE});

static std::unordered_set<DesignEntity> variableOnly = std::unordered_set<DesignEntity>({DesignEntity::VARIABLE});

/**
 * Get the corresponding Design Entity from the given string.
 *
 * @param str The string to obtain the Design Entity from.
 * @return The corresponding Design Entity.
 */
DesignEntity getDesignEntityFromStr(std::string str);

/**
 * Checks whether the Design Entity passed is valid.
 *
 * @param designEntity The Design Entity to be validated.
 * @return Returns true if the Design Entity passed belongs to the Enum class, and false otherwise.
 */
bool isValidDesignEntity(DesignEntity designEntity);

/**
 * Converts Design Entity object to string.
 *
 * @param designEntity The Design Entity to be converted to a string.
 * @return Returns the Design Entity passed in string.
 */
std::string toString(DesignEntity designEntity);
