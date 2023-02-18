#include "IntStringClause.h"
#include <utility>

IntStringClause::IntStringClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

std::unordered_set<ArgumentType> IntStringClause::getValidLeftArgumentType() {
    return std::unordered_set<ArgumentType> {
            ArgumentType::SYNONYM,
            ArgumentType::NUMBER,
            ArgumentType::WILDCARD
    };
}

std::unordered_set<ArgumentType> IntStringClause::getValidRightArgumentType() {
    return std::unordered_set<ArgumentType> {
            ArgumentType::SYNONYM,
            ArgumentType::WILDCARD,
            ArgumentType::CHARACTERSTRING
    };
}

std::unordered_set<DesignEntity> IntStringClause::getValidLeftDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::STMT,
            DesignEntity::ASSIGN,
            DesignEntity::WHILE,
            DesignEntity::CALL,
            DesignEntity::PRINT,
            DesignEntity::READ,
            DesignEntity::IF,
    };
}

std::unordered_set<DesignEntity> IntStringClause::getValidRightDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::VARIABLE
    };
}
