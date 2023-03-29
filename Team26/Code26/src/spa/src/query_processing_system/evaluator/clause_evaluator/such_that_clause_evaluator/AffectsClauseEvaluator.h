#pragma once

#include "IntIntClauseEvaluator.h"

class AffectsClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    AffectsClauseEvaluator(Argument left, Argument right);
};
