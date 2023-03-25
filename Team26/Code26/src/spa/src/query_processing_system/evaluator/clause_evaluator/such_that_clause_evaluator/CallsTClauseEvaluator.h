#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class CallsTClauseEvaluator : public StringStringClauseEvaluator {
 public:
    CallsTClauseEvaluator(Argument left, Argument right);

    EntityEntityMap getRelationshipManager() override;

    EntityEntityMap getOppositeRelationshipManager() override;
};
