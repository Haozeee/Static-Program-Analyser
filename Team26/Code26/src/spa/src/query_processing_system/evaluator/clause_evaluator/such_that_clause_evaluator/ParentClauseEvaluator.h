#pragma once

#include <memory>
#include "SuchThatClauseEvaluator.h"

class ParentClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    ParentClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
