#pragma once

#include "IntStringClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

class UsesSClauseEvaluator : public IntStringClauseEvaluator {
 public:
    UsesSClauseEvaluator(Argument left, Argument right);

    std::unordered_map<int, std::unordered_set<std::string>> getRelationshipManager(StoragePointer storage) override;

    std::unordered_map<std::string, std::unordered_set<int>>
    getOppositeRelationshipManager(StoragePointer storage) override;
};
