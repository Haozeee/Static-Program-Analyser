#pragma once

#include "IntIntClauseEvaluator.h"

class NextTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    NextTClauseEvaluator(Argument left, Argument right);

    IntIntMap getRelationshipManager() override;

    IntIntMap getOppositeRelationshipManager() override;

    IntIntMap getRelationshipCache(IntSet itemsToRead) override;

    IntIntMap getOppositeRelationshipCache(IntSet itemsToRead) override;

    bool isRelationshipEmpty() override;
};
