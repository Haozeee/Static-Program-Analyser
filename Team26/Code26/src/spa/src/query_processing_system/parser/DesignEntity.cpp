#include "DesignEntity.h"
#include <unordered_map>

std::unordered_map<std::string, DesignEntity> stringToDesignEntityMap = {
        {"stmt", DesignEntity::STMT},
        {"variable", DesignEntity::VARIABLE},
        {"procedure", DesignEntity::PROCEDURE},
        {"assign", DesignEntity::ASSIGN},
        {"read", DesignEntity::READ},
        {"print", DesignEntity::PRINT},
        {"call", DesignEntity::CALL},
        {"while", DesignEntity::WHILE},
        {"if", DesignEntity::IF},
        {"constant", DesignEntity::CONSTANT},
        {"none", DesignEntity::NONE},
};

std::unordered_map<DesignEntity, std::string> designEntityToStringMap({
      {DesignEntity::STMT, "stmt"},
      {DesignEntity::VARIABLE, "variable"},
      {DesignEntity::PROCEDURE, "procedure"},
      {DesignEntity::ASSIGN, "assign"},
      {DesignEntity::READ, "read"},
      {DesignEntity::PRINT, "print"},
      {DesignEntity::CALL, "call"},
      {DesignEntity::WHILE, "while"},
      {DesignEntity::IF, "if"},
      {DesignEntity::CONSTANT, "constant"},
      {DesignEntity::NONE, "none"},
});

DesignEntity getDesignEntityFromStr(std::string str) {
    auto iterator = stringToDesignEntityMap.find(str);
    if (iterator == stringToDesignEntityMap.end()) {
        return DesignEntity::NONE;
    }
    return iterator->second;
}

bool isValidDesignEntity(DesignEntity designEntity) {
    return (designEntity == DesignEntity::STMT
            || designEntity == DesignEntity::VARIABLE
            || designEntity == DesignEntity::PROCEDURE
            || designEntity == DesignEntity::ASSIGN);
}

std::string toString(DesignEntity designEntity) {
    auto result = designEntityToStringMap.find(designEntity);
    // throw exception here if design entity not found
    return result->second;
}
