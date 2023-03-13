#pragma once

#include "IntIntClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>

class AffectsClauseEvaluator : public IntIntClauseEvaluator {
 public:
    AffectsClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int, std::unordered_set<int>> getRelationshipManager() override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager() override;

    std::unordered_map<int, std::unordered_set<int>> getRelationshipCache(std::unordered_set<int> itemsToRead) override;

    std::unordered_map<int, std::unordered_set<int>>
    getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) override;

    bool isRelationshipEmpty() override;
};