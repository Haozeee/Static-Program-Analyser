#pragma once

#include "IntStringClauseEvaluator.h"
#include <string>

class ModifiesSClauseEvaluator : public IntStringClauseEvaluator {
 public:
    ModifiesSClauseEvaluator(Argument left, Argument right);

    IntStringMap getRelationshipManager() override;

    StringIntMap getOppositeRelationshipManager() override;
};
