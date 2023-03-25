#pragma once
#include "SuchThatClauseEvaluator.h"
#include <memory>
#include <string>

class IntIntClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 protected:
    IntIntClauseEvaluator(Argument left, Argument right);

    void evaluateEqualSynonym() override;

    void setLeftArgResult(StmtSet result) override;

    void setRightArgResult(StmtSet result) override;

    void setLeftAndRightArgResult(StmtStmtMap results) override;

    StmtSet getLeftArgEntities() override;

    StmtSet getRightArgEntities() override;

    int getLeftArg() override;

    int getRightArg() override;

    bool isLeftArgAmbiguous() override;

    bool isRightArgAmbiguous() override;
};
