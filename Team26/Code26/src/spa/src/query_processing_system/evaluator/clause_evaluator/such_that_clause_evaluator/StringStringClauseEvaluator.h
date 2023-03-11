#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

class StringStringClauseEvaluator : public SuchThatClauseEvaluator<std::string, std::string> {
 protected:
    StringStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<std::string> result) override;

    void setRightArgResult(std::unordered_set<std::string> result) override;

    void setLeftAndRightArgResult(std::unordered_map<std::string , std::unordered_set<std::string>> results) override;

    std::unordered_set<std::string> getLeftArgEntities() override;

    std::unordered_set<std::string> getRightArgEntities() override;

    void handleLeftWildcard() override;

    void handleRightWildcard() override;

    std::string getLeftArg() override;

    std::string getRightArg() override;

    bool isLeftArgAmbiguous() override;

    bool isRightArgAmbiguous() override;
};
