#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class CallsClauseEvaluator : public StringStringClauseEvaluator {
 public:
    CallsClauseEvaluator(Argument left, Argument right);

    EntityEntityMap getRelationshipManager() override;

    EntityEntityMap getOppositeRelationshipManager() override;
};
