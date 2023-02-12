#pragma once

#include <memory>
#include "SuchThatClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>

class ModifiesPClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 public:
    ModifiesPClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(StoragePointer storage) override;

    std::unordered_map<int , std::unordered_set<int>> getRelationshipManager(StoragePointer storage) override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager(StoragePointer storage) override;

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<int> result) override;

    std::unordered_set<int> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<int> getRightArgEntities(StoragePointer storage) override;
};