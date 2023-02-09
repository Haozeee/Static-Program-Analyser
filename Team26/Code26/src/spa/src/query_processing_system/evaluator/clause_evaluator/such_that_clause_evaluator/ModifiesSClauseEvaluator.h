#pragma once

#include <memory>
#include "SuchThatClauseEvaluator.h"

class ModifiesSClauseEvaluator : public SuchThatClauseEvaluator {
 public:
    ModifiesSClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
