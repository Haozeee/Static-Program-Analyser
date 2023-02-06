#pragma once
#include <string>
#include <ostream>
#include <unordered_map>

enum class DesignEntity {
    STMT,
    VARIABLE,
    PROCEDURE,
    ASSIGN,
    NONE
};

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