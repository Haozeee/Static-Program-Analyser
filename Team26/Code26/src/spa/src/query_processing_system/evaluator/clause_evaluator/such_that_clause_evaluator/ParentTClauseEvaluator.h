#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>

class ParentTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    ParentTClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;
};
