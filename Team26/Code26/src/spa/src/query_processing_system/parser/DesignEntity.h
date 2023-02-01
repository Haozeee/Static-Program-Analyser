#pragma once
#include "string"

enum class DesignEntity {
    STMT,
    VARIABLE,
    PROCEDURE,
    ASSIGN,
    NONE
};

/**
 * Get the corresponding design entity from the given string.
 * @param str The string to obtain the design entity from.
 * @return The corresponding design entity.
 */
DesignEntity getDesignEntityFromStr(std::string str);
