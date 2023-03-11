#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "PatternClauseEvaluator.h"
#include "IfAndWhilePatternClauseEvaluator.h"

class IfPatternClauseEvaluator : public IfAndWhilePatternClauseEvaluator {
 protected:
    std::unordered_map<int, std::unordered_set<std::string>>
        getRelationshipEntries(std::shared_ptr<ReadStorage>) override;

    std::unordered_map<std::string, std::unordered_set<int>>
        getReverseRelationshipEntries(std::shared_ptr<ReadStorage>) override;

 public:
    IfPatternClauseEvaluator(Argument patternArg, Argument leftArg);
};
