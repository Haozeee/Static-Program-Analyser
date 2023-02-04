#pragma once
#include <string>
#include <ostream>

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
