#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class FollowsClause : public IntIntClause {
 public:
    FollowsClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
