#pragma once

#include "IntIntClauseEvaluator.h"

class ParentClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    ParentClauseEvaluator(Argument left, Argument right);
};
