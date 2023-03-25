#pragma once

#include "IntStringClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

class UsesSClauseEvaluator : public IntStringClauseEvaluator {
 public:
    UsesSClauseEvaluator(Argument left, Argument right);

    IntStringMap getRelationshipManager() override;

    StringIntMap getOppositeRelationshipManager() override;
};
