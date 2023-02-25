#pragma once

#include <utility>
#include <string>
#include <unordered_set>
#include "../../DesignEntity.h"
#include "../../Synonym.h"

std::string statementNum = "stmt#";
std::string value = "value";
std::string varName = "varName";
std::string procName = "procName";

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
    AttributeReference(DesignEntity designEntity, std::string synonym, std::string attributeName);

    bool isValidAttributeReference();

    bool isStringAttributeReference();

    bool isIntAttributeReference();
};
