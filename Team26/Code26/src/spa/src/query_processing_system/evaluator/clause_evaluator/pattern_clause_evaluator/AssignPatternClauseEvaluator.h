#pragma once

#include <memory>

#include "PatternClauseEvaluator.h"

class AssignPatternClauseEvaluator : public PatternClauseEvaluator {
 public:
    AssignPatternClauseEvaluator(Argument leftArg, std::variant<Wildcard, StringExpression> rightArg);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
