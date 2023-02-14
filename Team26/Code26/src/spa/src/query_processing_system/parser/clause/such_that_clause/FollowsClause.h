#pragma once

#include "IntIntClause.h"

class FollowsClause : public IntIntClause {
 public:
    FollowsClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
