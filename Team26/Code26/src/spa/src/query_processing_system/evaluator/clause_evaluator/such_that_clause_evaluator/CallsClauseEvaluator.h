#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "StringStringClauseEvaluator.h"

class CallsClauseEvaluator : public StringStringClauseEvaluator {
 public:
    CallsClauseEvaluator(Argument left, Argument right);

    StringStringMap getRelationshipManager() override;

    StringStringMap getOppositeRelationshipManager() override;
};
