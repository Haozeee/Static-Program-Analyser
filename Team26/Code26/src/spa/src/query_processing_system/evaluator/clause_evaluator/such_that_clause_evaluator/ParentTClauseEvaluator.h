#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>

class ParentTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    ParentTClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;
};
