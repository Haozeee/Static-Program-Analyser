#pragma once
#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"
#include "ExpressionlessPatternClauseEvaluator.h"

class IfPatternClauseEvaluator : public ExpressionlessPatternClauseEvaluator {
 protected:
    IntStringMap getRelationshipEntries() override;

    StringIntMap getReverseRelationshipEntries() override;

 public:
    IfPatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
