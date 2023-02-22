#include "StringStringClause.h"
#include <utility>

StringStringClause::StringStringClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

std::unordered_set<ArgumentType> StringStringClause::getValidLeftArgumentType() {
    return std::unordered_set<ArgumentType> {
            ArgumentType::SYNONYM,
            ArgumentType::WILDCARD,
            ArgumentType::CHARACTERSTRING
    };
}

std::unordered_set<ArgumentType> StringStringClause::getValidRightArgumentType() {
    return getValidLeftArgumentType();
}

std::unordered_set<DesignEntity> StringStringClause::getValidLeftDesignEntity() {
    return std::unordered_set<DesignEntity> {
            DesignEntity::PROCEDURE
    };
}

