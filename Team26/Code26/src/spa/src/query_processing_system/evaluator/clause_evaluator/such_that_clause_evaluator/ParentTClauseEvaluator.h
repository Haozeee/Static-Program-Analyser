#pragma once

#include "IntIntClauseEvaluator.h"
#include <memory>

class ParentTClauseEvaluator : public IntIntClauseEvaluator {
 protected:
    StmtStmtMap getRelationshipMap(StmtSet &interestedValues) override;

    StmtStmtMap getOppositeRelationshipMap(StmtSet &interestedValues) override;

    bool isEmptyRelation() override;

public:
    ParentTClauseEvaluator(Argument left, Argument right);
};
