#pragma once
#include "IntIntClauseEvaluator.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>

class NextClauseEvaluator : public IntIntClauseEvaluator {
 public:
    NextClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;
};
