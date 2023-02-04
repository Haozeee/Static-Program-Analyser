#pragma once
#include "../Clause.h"
#include "../../Argument.h"

class SuchThatClause : public Clause {
 private:
    Argument leftArg;
    Argument rightArg;

 public:
    SuchThatClause(Argument left, Argument right);

    virtual ~SuchThatClause() = default;

    Argument getLeftArg();

    Argument getRightArg();
};
