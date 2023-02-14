#pragma once

#include "IntIntClause.h"

class FollowsTClause : public IntIntClause {
 public:
    FollowsTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
