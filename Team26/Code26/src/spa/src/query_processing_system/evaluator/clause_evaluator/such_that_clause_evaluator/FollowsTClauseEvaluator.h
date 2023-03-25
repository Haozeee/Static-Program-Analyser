#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>

class FollowsTClauseEvaluator : public IntIntClauseEvaluator {
 public:
    FollowsTClauseEvaluator(Argument left, Argument right);

    StmtStmtMap getRelationshipManager() override;

    StmtStmtMap getOppositeRelationshipManager() override;
};
