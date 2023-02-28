#pragma once

#include <utility>
#include <string>
#include <unordered_map>
#include "../../DesignEntity.h"
#include "../../Synonym.h"

const char statementNum[] = "stmt#";
const char value[] = "value";
const char varName[] = "varName";
const char procName[] = "procName";

std::unordered_map<DesignEntity, std::string> validIntAttributes {
        {DesignEntity::STMT, statementNum},
        {DesignEntity::READ, statementNum},
        {DesignEntity::PRINT, statementNum},
        {DesignEntity::CALL, statementNum},
        {DesignEntity::WHILE, statementNum},
        {DesignEntity::IF, statementNum},
        {DesignEntity::ASSIGN, statementNum},
        {DesignEntity::CONSTANT, value}
};

std::unordered_map<DesignEntity, std::string> validStringAttributes {
        {DesignEntity::PROCEDURE, procName},
        {DesignEntity::CALL, procName},
        {DesignEntity::VARIABLE, varName},
        {DesignEntity::READ, varName},
        {DesignEntity::PRINT, varName}
};

class AttributeReference {
 private:
    DesignEntity designEntity;

    std::string synonym;

    std::string attributeName;

 public:
    /**
     * If the attribute is "p1.stmt#", the design entity is PRINT, the synonym is "p1"
     * and the attributeName is "stmt#".
     */
    AttributeReference(DesignEntity designEntity, std::string synonym, std::string attributeName);

    bool isValidAttributeReference();

    /**
     * Checks if this attribute reference refers to a string.
     */
    bool isStringAttributeReference();

    /**
     * Checks if this attribute reference refers to an integer.
     */
    bool isIntAttributeReference();

    std::string getSynonym();

    DesignEntity getDesignEntity();
};
