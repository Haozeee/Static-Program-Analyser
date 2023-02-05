#include "DesignEntity.h"
#include <unordered_map>

std::unordered_map<std::string, DesignEntity> stringToDesignEntityMap = {
        {"stmt", DesignEntity::STMT},
        {"variable", DesignEntity::VARIABLE},
        {"procedure", DesignEntity::PROCEDURE},
        {"assign", DesignEntity::ASSIGN}
};

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
