#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>

class ParentTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    ParentTClauseEvaluator(Argument left, Argument right);

    StmtStmtMap getRelationshipManager() override;

    StmtStmtMap getOppositeRelationshipManager() override;
};
