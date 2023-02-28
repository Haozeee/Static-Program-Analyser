#pragma once
#include "IntIntClauseEvaluator.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>

class NextClauseEvaluator : public IntIntClauseEvaluator {
public:
    NextClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int, std::unordered_set<int>> getRelationshipManager(StoragePointer storage) override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager(StoragePointer storage) override;
};
