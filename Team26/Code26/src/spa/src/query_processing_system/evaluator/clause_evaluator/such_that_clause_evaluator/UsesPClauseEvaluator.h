#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class UsesPClauseEvaluator : public StringStringClauseEvaluator {
 public:
    UsesPClauseEvaluator(Argument left, Argument right);

    StringStringMap getRelationshipManager() override;

    StringStringMap getOppositeRelationshipManager() override;
};
