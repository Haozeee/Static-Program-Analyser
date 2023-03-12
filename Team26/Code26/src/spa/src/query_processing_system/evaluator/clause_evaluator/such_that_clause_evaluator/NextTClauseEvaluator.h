#pragma once

#include "IntIntClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>

class NextTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    NextTClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int, std::unordered_set<int>> getRelationshipManager() override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager() override;

    std::unordered_map<int, std::unordered_set<int>> getRelationshipCache(std::unordered_set<int> itemsToRead) override;

    std::unordered_map<int, std::unordered_set<int>>
    getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) override;
};
