#pragma once
#include "IntIntClauseEvaluator.h"
#include <memory>

class FollowsClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    FollowsClauseEvaluator(Argument left, Argument right);
};
