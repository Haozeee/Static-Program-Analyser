#pragma once
#include "IntIntClauseEvaluator.h"
#include <memory>

class NextClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

public:
    NextClauseEvaluator(Argument left, Argument right);
};
