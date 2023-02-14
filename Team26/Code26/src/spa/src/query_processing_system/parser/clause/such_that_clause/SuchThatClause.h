#pragma once

#include <utility>
#include <unordered_set>

#include "../Clause.h"
#include "../../Argument.h"

using ValidArgumentType = std::pair<ArgTypeIndex, ArgTypeIndex>;
using ValidDesignEntity = std::pair<std::unordered_set<DesignEntity>, std::unordered_set<DesignEntity>>;

class SuchThatClause : public Clause {
 private:
    Argument leftArg;
    Argument rightArg;

 public:
    SuchThatClause(Argument left, Argument right);

    virtual ~SuchThatClause() = default;

    Argument getLeftArg();

    Argument getRightArg();

    virtual ValidArgumentType getValidArgumentType() = 0;

    virtual ValidDesignEntity getValidDesignEntity() = 0;
};
