#pragma once

#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"


class WhilePatternClauseEvaluator : public PatternClauseEvaluator {
 protected:
    void evaluateSynonym(std::shared_ptr<ReadStorage>) override;

    void evaluateString(std::shared_ptr<ReadStorage>) override;

    void evaluateWildcard(std::shared_ptr<ReadStorage>) override;

public:
    WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg);

    std::shared_ptr<ResultTable> evaluateClause(std::shared_ptr<ReadStorage> storage) override;
};
