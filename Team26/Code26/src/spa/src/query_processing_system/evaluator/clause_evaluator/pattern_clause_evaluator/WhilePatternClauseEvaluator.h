#pragma once

#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"


class WhilePatternClauseEvaluator : public PatternClauseEvaluator {
 public:
    WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg);

    std::shared_ptr<ResultTable> evaluateClause(std::shared_ptr<ReadStorage> storage) override;
};
