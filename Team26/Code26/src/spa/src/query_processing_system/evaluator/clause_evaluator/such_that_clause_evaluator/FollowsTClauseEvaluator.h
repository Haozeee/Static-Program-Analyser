#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>

class FollowsTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    FollowsTClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;
};
