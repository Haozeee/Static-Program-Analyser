#pragma once
#include "SuchThatClause.h"

class UsesClause : public SuchThatClause {
 public:
    UsesClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};

