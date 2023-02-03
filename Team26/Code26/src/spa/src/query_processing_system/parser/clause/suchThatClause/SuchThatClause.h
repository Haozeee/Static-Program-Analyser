#pragma once
#include "../Clause.h"
#include "../../Argument.h"

class SuchThatClause : Clause {
private:
    Argument leftArg;
    Argument rightArg;

public:
    SuchThatClause(Argument left, Argument right);

    Argument getLeftArg();

    Argument getRightArg();
};
