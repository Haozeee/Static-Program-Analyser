#pragma once
#include "SuchThatClauseEvaluator.h"

class FollowsClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    FollowsClauseEvaluator(Argument left, Argument right);

    bool evaluateClause() override;
};
