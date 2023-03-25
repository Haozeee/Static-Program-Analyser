#pragma once

#include "IntIntClauseEvaluator.h"

class AffectsClauseEvaluator : public IntIntClauseEvaluator {
 public:
    AffectsClauseEvaluator(Argument left, Argument right);

    StmtStmtMap getRelationshipManager() override;

    StmtStmtMap getOppositeRelationshipManager() override;

    StmtStmtMap getRelationshipCache(StmtSet itemsToRead) override;

    StmtStmtMap getOppositeRelationshipCache(StmtSet itemsToRead) override;

    bool isRelationshipEmpty() override;
};
