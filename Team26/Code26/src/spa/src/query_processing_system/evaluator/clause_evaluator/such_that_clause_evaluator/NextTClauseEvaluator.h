#pragma once

#include "IntIntClauseEvaluator.h"

class NextTClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

public:
    NextTClauseEvaluator(Argument left, Argument right);
};
