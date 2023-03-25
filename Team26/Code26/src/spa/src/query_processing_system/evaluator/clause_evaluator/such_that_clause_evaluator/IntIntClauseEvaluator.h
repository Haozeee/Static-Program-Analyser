#pragma once
#include "SuchThatClauseEvaluator.h"
#include <memory>
#include <string>

class IntIntClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 protected:
    IntIntClauseEvaluator(Argument left, Argument right);

    void evaluateEqualSynonym() override;

    void setLeftArgResult(IntSet result) override;

    void setRightArgResult(IntSet result) override;

    void setLeftAndRightArgResult(IntIntMap results) override;

    IntSet getLeftArgEntities() override;

    IntSet getRightArgEntities() override;

    int getLeftArg() override;

    int getRightArg() override;

    bool isLeftArgAmbiguous() override;

    bool isRightArgAmbiguous() override;
};
