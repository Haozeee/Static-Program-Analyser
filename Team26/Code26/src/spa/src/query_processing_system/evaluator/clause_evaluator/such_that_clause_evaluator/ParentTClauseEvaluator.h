#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>

class ParentTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    ParentTClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int , std::unordered_set<int>> getRelationshipManager() override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager() override;
};
