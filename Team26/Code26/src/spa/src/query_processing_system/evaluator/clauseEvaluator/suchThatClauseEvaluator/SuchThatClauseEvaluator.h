#pragma once
#include "../ClauseEvaluator.h"
#include "../../../parser/Argument.h"

class SuchThatClauseEvaluator : public ClauseEvaluator {
 private:
    Argument leftArg;
    Argument rightArg;

 public:
    SuchThatClauseEvaluator(Argument left, Argument right);

    Argument getLeftArg();

    Argument getRightArg();
};
