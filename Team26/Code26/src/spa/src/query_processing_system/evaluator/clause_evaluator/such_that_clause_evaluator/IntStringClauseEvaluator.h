#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

class IntStringClauseEvaluator : public SuchThatClauseEvaluator<int, std::string> {
 protected:
    IntStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<std::string> result) override;

    void setLeftAndRightArgResult(std::unordered_map<int, std::unordered_set<std::string>> results) override;

    std::unordered_set<int> getLeftArgEntities() override;

    std::unordered_set<std::string> getRightArgEntities() override;

    void handleLeftWildcard() override;

    int getLeftArg() override;

    std::string getRightArg() override;

    bool isRightArgAmbiguous() override;
};
