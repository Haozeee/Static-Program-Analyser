#pragma once

#include <memory>
#include "SuchThatClauseEvaluator.h"

class UsesSClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    UsesSClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
