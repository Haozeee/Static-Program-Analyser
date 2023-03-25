#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>

class FollowsTClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    FollowsTClauseEvaluator(Argument left, Argument right);
};
