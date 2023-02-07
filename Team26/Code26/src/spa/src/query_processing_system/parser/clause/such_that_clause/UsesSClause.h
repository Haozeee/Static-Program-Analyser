#pragma once

#include "SuchThatClause.h"

class UsesSClause : public SuchThatClause {
 public:
    UsesSClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};

