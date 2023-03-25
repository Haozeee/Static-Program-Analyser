#pragma once

#include "IntIntClauseEvaluator.h"

class ParentClauseEvaluator : public IntIntClauseEvaluator {
 public:
    ParentClauseEvaluator(Argument left, Argument right);

    StmtStmtMap getRelationshipManager() override;

    StmtStmtMap getOppositeRelationshipManager() override;
};
