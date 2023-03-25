#pragma once

#include "IntStringClauseEvaluator.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

class ModifiesSClauseEvaluator : public IntStringClauseEvaluator {
 public:
    ModifiesSClauseEvaluator(Argument left, Argument right);

    IntStringMap getRelationshipManager() override;

    StringIntMap getOppositeRelationshipManager() override;
};
