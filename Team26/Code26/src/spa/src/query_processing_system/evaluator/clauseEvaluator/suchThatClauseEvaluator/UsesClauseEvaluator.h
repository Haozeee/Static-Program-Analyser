#pragma once
#include "SuchThatClauseEvaluator.h"

class UsesClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    UsesClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
