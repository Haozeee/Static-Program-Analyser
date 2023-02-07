#pragma once

#include <memory>
#include "SuchThatClauseEvaluator.h"

class ModifiesPClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    ModifiesPClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
