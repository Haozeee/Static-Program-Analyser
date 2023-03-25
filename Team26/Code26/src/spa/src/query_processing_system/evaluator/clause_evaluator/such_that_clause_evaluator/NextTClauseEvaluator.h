#pragma once

#include "IntIntClauseEvaluator.h"

class NextTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    NextTClauseEvaluator(Argument left, Argument right);

    StmtStmtMap getRelationshipManager() override;

    StmtStmtMap getOppositeRelationshipManager() override;

    StmtStmtMap getRelationshipCache(StmtSet itemsToRead) override;

    StmtStmtMap getOppositeRelationshipCache(StmtSet itemsToRead) override;

    bool isRelationshipEmpty() override;
};
