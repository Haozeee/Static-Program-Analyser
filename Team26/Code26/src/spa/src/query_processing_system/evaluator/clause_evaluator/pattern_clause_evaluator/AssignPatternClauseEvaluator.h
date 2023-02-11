#pragma once

#include <memory>
#include <variant>

#include "PatternClauseEvaluator.h"

class AssignPatternClauseEvaluator : public PatternClauseEvaluator {
 public:
    AssignPatternClauseEvaluator(DesignEntity designEntity, Argument leftArg, StringExpression rightArg);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
