#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <memory>

class StringStringClauseEvaluator : public SuchThatClauseEvaluator<std::string, std::string> {
 protected:
    StringStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(EntitySet result) override;

    void setRightArgResult(EntitySet result) override;

    void setLeftAndRightArgResult(EntityEntityMap results) override;

    EntitySet getLeftArgEntities() override;

    EntitySet getRightArgEntities() override;

    std::string getLeftArg() override;

    std::string getRightArg() override;

    bool isLeftArgAmbiguous() override;

    bool isRightArgAmbiguous() override;
};
