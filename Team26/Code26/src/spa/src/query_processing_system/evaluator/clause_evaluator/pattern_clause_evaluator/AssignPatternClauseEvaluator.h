#pragma once

#include <memory>
#include <variant>

#include "PatternClauseEvaluator.h"

class AssignPatternClauseEvaluator : public PatternClauseEvaluator {
 public:
    AssignPatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg);

    std::shared_ptr<ResultTable> evaluateClause(std::shared_ptr<ReadStroage> storage) override;
};
