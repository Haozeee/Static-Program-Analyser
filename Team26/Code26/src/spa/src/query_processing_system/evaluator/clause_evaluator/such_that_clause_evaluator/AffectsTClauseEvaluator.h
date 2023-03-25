#pragma once

#include "IntIntClauseEvaluator.h"

class AffectsTClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

public:
    AffectsTClauseEvaluator(Argument left, Argument right);
};
