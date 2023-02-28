#include "AttributeReference.h"

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

AttributeReference::AttributeReference(DesignEntity designEntity, std::string synonym, std::string attributeName)
    : designEntity(designEntity), synonym(synonym), attributeName(attributeName) {}

bool AttributeReference::isStringAttributeReference() {
    auto it = validStringAttributes.find(designEntity);
    return it != validStringAttributes.end() && it->second == attributeName;
}


bool AttributeReference::isIntAttributeReference() {
    auto it = validIntAttributes.find(designEntity);
    return it != validIntAttributes.end() && it->second == attributeName;
}

bool AttributeReference::isValidAttributeReference() {
    return isStringAttributeReference() || isIntAttributeReference();
}

std::string AttributeReference::getSynonym() {
    return synonym;
}

DesignEntity AttributeReference::getDesignEntity() {
    return designEntity;
}
