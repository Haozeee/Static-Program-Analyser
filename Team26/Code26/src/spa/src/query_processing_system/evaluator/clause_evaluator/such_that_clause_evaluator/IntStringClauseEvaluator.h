#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

class IntStringClauseEvaluator : public SuchThatClauseEvaluator<int, std::string> {
 protected:
    IntStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(IntSet result) override;

    void setRightArgResult(StringSet result) override;

    void setLeftAndRightArgResult(IntStringMap results) override;

    IntSet getLeftArgEntities() override;

    StringSet getRightArgEntities() override;

    int getLeftArg() override;

    std::string getRightArg() override;

    bool isLeftArgAmbiguous() override;

    bool isRightArgAmbiguous() override;
};
