#pragma once

#include <memory>
#include "SuchThatClauseEvaluator.h"

class ParentTClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    ParentTClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
