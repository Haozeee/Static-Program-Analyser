#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

class StringStringClauseEvaluator : public SuchThatClauseEvaluator<std::string, std::string> {
 protected:
    StringStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(StringSet result) override;

    void setRightArgResult(StringSet result) override;

    void setLeftAndRightArgResult(StringStringMap results) override;

    StringSet getLeftArgEntities() override;

    StringSet getRightArgEntities() override;

    std::string getLeftArg() override;

    std::string getRightArg() override;

    bool isLeftArgAmbiguous() override;

    bool isRightArgAmbiguous() override;
};
