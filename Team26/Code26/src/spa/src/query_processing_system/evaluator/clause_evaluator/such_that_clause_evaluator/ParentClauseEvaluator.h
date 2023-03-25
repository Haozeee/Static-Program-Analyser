#pragma once

#include "IntIntClauseEvaluator.h"

class ParentClauseEvaluator : public IntIntClauseEvaluator {
 public:
    ParentClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;
};
