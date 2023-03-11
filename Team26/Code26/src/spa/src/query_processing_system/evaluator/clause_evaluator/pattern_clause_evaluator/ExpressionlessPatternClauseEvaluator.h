#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "PatternClauseEvaluator.h"

class ExpressionlessPatternClauseEvaluator : public PatternClauseEvaluator {
 protected:
    void evaluateSynonym() override;

    void evaluateString() override;

    void evaluateWildcard() override;

    virtual std::unordered_map<int, std::unordered_set<std::string>> getRelationshipEntries() = 0;

    virtual std::unordered_map<std::string, std::unordered_set<int>> getReverseRelationshipEntries() = 0;

 public:
    ExpressionlessPatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
