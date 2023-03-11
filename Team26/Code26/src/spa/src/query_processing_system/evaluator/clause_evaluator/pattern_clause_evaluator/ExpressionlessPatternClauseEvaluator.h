#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "PatternClauseEvaluator.h"

class ExpressionlessPatternClauseEvaluator : public PatternClauseEvaluator {
 protected:
    void evaluateSynonym(std::shared_ptr<ReadStorage>) override;

    void evaluateString(std::shared_ptr<ReadStorage>) override;

    void evaluateWildcard(std::shared_ptr<ReadStorage>) override;

    virtual std::unordered_map<int, std::unordered_set<std::string>>
        getRelationshipEntries(std::shared_ptr<ReadStorage>) = 0;

    virtual std::unordered_map<std::string, std::unordered_set<int>>
        getReverseRelationshipEntries(std::shared_ptr<ReadStorage>) = 0;

 public:
    ExpressionlessPatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
