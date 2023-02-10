#pragma once

#include "IntIntClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>

class ParentClauseEvaluator : public IntIntClauseEvaluator {
 public:
    ParentClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int, std::unordered_set<int>> getRelationshipManager(StoragePointer storage) override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager(StoragePointer storage) override;
};
