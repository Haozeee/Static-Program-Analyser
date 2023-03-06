#pragma once

#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"

class IfPatternClauseEvaluator : public PatternClauseEvaluator {
 public:
    IfPatternClauseEvaluator(Argument patternArg, Argument leftArg);

    std::shared_ptr<ResultTable> evaluateClause(std::shared_ptr<ReadStorage> storage) override;
};
