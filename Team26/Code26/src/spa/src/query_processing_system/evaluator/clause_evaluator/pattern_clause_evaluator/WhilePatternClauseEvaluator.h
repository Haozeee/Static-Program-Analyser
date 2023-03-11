#pragma once

#include <memory>
#include <string>
#include "PatternClauseEvaluator.h"
#include "IfAndWhilePatternClauseEvaluator.h"

class WhilePatternClauseEvaluator : public IfAndWhilePatternClauseEvaluator {
 protected:
    std::unordered_map<int, std::unordered_set<std::string>>
        getRelationshipEntries(std::shared_ptr<ReadStorage> storage) override;

    std::unordered_map<std::string, std::unordered_set<int>>
        getReverseRelationshipEntries(std::shared_ptr<ReadStorage>) override;

 public:
    WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
