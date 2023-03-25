#pragma once
#include "IntIntClauseEvaluator.h"
#include <memory>

class NextClauseEvaluator : public IntIntClauseEvaluator {
 public:
    NextClauseEvaluator(Argument left, Argument right);

    StmtStmtMap getRelationshipManager() override;

    StmtStmtMap getOppositeRelationshipManager() override;
};
