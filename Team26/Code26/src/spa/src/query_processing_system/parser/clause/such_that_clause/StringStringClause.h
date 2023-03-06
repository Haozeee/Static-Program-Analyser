#pragma once
#include "SuchThatClause.h"
#include <unordered_set>

class StringStringClause : public SuchThatClause {
 protected:
    StringStringClause(Argument leftArg, Argument rightArg);

    std::unordered_set<ArgumentType> getValidLeftArgumentType() override;

    std::unordered_set<ArgumentType> getValidRightArgumentType() override;

    std::unordered_set<DesignEntity> getValidLeftDesignEntity() override;
};
