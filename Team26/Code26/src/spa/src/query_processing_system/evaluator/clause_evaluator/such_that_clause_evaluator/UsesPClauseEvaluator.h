#pragma once

#include <memory>
#include "SuchThatClauseEvaluator.h"

class UsesPClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    UsesPClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
