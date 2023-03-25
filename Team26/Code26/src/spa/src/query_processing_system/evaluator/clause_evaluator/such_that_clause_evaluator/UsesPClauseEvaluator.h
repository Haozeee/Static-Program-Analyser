#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class UsesPClauseEvaluator : public StringStringClauseEvaluator {
 public:
    UsesPClauseEvaluator(Argument left, Argument right);

    EntityEntityMap getRelationshipManager() override;

    EntityEntityMap getOppositeRelationshipManager() override;
};
