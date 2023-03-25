#pragma once
#include "IntIntClauseEvaluator.h"
#include <memory>

class FollowsClauseEvaluator : public IntIntClauseEvaluator {
 public:
    FollowsClauseEvaluator(Argument left, Argument right);

    StmtStmtMap getRelationshipManager() override;

    StmtStmtMap getOppositeRelationshipManager() override;
};
