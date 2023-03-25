#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>

class FollowsTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    FollowsTClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;
};
