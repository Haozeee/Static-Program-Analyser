#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "PatternClauseEvaluator.h"
#include "ExpressionlessPatternClauseEvaluator.h"

class IfPatternClauseEvaluator : public ExpressionlessPatternClauseEvaluator {
 protected:
    IntStringMap getRelationshipEntries() override;

    StringIntMap getReverseRelationshipEntries() override;

 public:
    IfPatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
