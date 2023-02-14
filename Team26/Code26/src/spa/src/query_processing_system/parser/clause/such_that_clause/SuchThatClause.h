#pragma once

#include <unordered_set>
#include "SuchThatClauseValidationResult.h"
#include "../Clause.h"
#include "../../Argument.h"

class SuchThatClause : public Clause {
 private:
    Argument leftArg;

    Argument rightArg;

 protected:
    SuchThatClause(Argument left, Argument right);

    virtual std::unordered_set<ArgumentType> getValidLeftArgumentType() = 0;

    virtual std::unordered_set<ArgumentType> getValidRightArgumentType() = 0;

    virtual std::unordered_set<DesignEntity> getValidLeftDesignEntity() = 0;

    virtual std::unordered_set<DesignEntity> getValidRightDesignEntity() = 0;

 public:
    virtual ~SuchThatClause() = default;

    SuchThatClauseValidationResult isValidClause();

    Argument getLeftArg();

    Argument getRightArg();
};
