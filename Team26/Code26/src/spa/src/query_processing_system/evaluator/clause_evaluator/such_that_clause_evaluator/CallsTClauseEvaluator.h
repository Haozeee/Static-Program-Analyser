#pragma once

#include <memory>
#include <string>
#include "StringStringClauseEvaluator.h"

class CallsTClauseEvaluator : public StringStringClauseEvaluator {
 public:
    CallsTClauseEvaluator(Argument left, Argument right);

    StringStringMap getRelationshipManager() override;

    StringStringMap getOppositeRelationshipManager() override;
};
