#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <memory>

class IntStringClauseEvaluator : public SuchThatClauseEvaluator<int, std::string> {
 protected:
    IntStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(StmtSet result) override;

    void setRightArgResult(EntitySet result) override;

    void setLeftAndRightArgResult(StmtEntityMap results) override;

    StmtSet getLeftArgEntities() override;

    EntitySet getRightArgEntities() override;

    int getLeftArg() override;

    std::string getRightArg() override;

    bool isLeftArgAmbiguous() override;

    bool isRightArgAmbiguous() override;
};
