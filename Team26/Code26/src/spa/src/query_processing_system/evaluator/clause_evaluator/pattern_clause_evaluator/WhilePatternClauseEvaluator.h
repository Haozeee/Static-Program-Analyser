#pragma once
#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"
#include "ExpressionlessPatternClauseEvaluator.h"

class WhilePatternClauseEvaluator : public ExpressionlessPatternClauseEvaluator {
 protected:
    IntStringMap getRelationshipEntries() override;

    StringIntMap getReverseRelationshipEntries() override;

 public:
    WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
