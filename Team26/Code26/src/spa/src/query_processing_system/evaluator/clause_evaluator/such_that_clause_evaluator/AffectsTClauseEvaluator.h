#pragma once

#include "IntIntClauseEvaluator.h"

class AffectsTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    AffectsTClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;

    IntIntMap getRelationshipCache(IntSet itemsToRead) override;

    IntIntMap getOppositeRelationshipCache(IntSet itemsToRead) override;

    bool isRelationshipEmpty() override;
};
