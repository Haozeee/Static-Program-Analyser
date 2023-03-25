#pragma once

#include "IntIntClauseEvaluator.h"

class AffectsClauseEvaluator : public IntIntClauseEvaluator {
 public:
    AffectsClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;

    IntIntMap getRelationshipCache(IntSet itemsToRead) override;

    IntIntMap getOppositeRelationshipCache(IntSet itemsToRead) override;

    bool isRelationshipEmpty() override;
};
