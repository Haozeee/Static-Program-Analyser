#include "IntIntClause.h"
#include <utility>

IntIntClause::IntIntClause(Argument leftArg, Argument rightArg)
        : SuchThatClause(std::move(leftArg), std::move(rightArg)) {}

std::unordered_set<ArgumentType> IntIntClause::getValidLeftArgumentType() {
    return std::unordered_set<ArgumentType> {
        ArgumentType::SYNONYM,
        ArgumentType::WILDCARD,
        ArgumentType::NUMBER,
    };
}

std::unordered_set<ArgumentType> IntIntClause::getValidRightArgumentType() {
    return getValidLeftArgumentType();
}

std::unordered_set<DesignEntity> IntIntClause::getValidLeftDesignEntity() {
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

std::unordered_set<DesignEntity> IntIntClause::getValidRightDesignEntity() {
    return getValidLeftDesignEntity();
}
