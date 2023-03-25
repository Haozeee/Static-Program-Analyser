#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "PatternClauseEvaluator.h"
#include "ExpressionlessPatternClauseEvaluator.h"

class WhilePatternClauseEvaluator : public ExpressionlessPatternClauseEvaluator {
 protected:
    IntStringMap getRelationshipEntries() override;

    StringIntMap getReverseRelationshipEntries() override;

 public:
    WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
