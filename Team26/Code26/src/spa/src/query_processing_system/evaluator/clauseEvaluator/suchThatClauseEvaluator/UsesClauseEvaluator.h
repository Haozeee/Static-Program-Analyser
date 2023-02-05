#pragma once
#include "SuchThatClauseEvaluator.h"

class UsesClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    UsesClauseEvaluator(Argument left, Argument right);

    bool evaluateClause() override;
};
