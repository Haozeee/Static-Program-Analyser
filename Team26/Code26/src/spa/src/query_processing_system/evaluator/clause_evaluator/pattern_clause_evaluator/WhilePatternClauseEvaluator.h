#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "PatternClauseEvaluator.h"
#include "ExpressionlessPatternClauseEvaluator.h"

class WhilePatternClauseEvaluator : public ExpressionlessPatternClauseEvaluator {
 protected:
    std::unordered_map<int, std::unordered_set<std::string>> getRelationshipEntries() override;

    std::unordered_map<std::string, std::unordered_set<int>> getReverseRelationshipEntries() override;

 public:
    WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
