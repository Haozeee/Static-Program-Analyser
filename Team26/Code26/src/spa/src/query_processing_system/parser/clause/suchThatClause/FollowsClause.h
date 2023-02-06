#pragma once
#include "SuchThatClause.h"

class FollowsClause : public SuchThatClause {
 public:
    FollowsClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
