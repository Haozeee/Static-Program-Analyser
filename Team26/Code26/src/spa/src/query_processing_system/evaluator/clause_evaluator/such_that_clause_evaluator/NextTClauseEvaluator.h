#pragma once

#include "IntIntClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>

class NextTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    NextTClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;

    IntIntMap getRelationshipCache(std::unordered_set<int> itemsToRead) override;

    IntIntMap getOppositeRelationshipCache(std::unordered_set<int> itemsToRead) override;

    bool isRelationshipEmpty() override;
};
