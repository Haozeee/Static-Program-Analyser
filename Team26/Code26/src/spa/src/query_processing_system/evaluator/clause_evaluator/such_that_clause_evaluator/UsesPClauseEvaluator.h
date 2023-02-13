#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "SuchThatClauseEvaluator.h"

class UsesPClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 public:
    UsesPClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override;

    std::unordered_map<int , std::unordered_set<int>> getRelationshipManager(StoragePointer storage) override;

    std::unordered_map<int, std::unordered_set<int>> getOppositeRelationshipManager(StoragePointer storage) override;

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<int> result) override;

    void setLeftAndRightArgResult(std::unordered_set<int> resultLeft, std::unordered_set<int> resultRight) override;

    std::unordered_set<int> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<int> getRightArgEntities(StoragePointer storage) override;
};
