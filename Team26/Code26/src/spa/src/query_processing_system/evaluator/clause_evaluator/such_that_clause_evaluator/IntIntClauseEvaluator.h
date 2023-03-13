#pragma once
#include "SuchThatClauseEvaluator.h"
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <string>

class IntIntClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 protected:
    IntIntClauseEvaluator(Argument left, Argument right, bool cacheable = false);

    void evaluateEqualSynonym() override;

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<int> result) override;

    void setLeftAndRightArgResult(std::unordered_map<int, std::unordered_set<int>> results) override;

    std::unordered_set<int> getLeftArgEntities() override;

    std::unordered_set<int> getRightArgEntities() override;

    void handleLeftWildcard() override;

    int getLeftArg() override;

    int getRightArg() override;
};
