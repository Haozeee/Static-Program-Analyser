#pragma once

#include "IntStringClauseEvaluator.h"
#include <string>

class UsesSClauseEvaluator : public IntStringClauseEvaluator {
 protected:
    StmtEntityMap getRelationshipMap(StmtSet &interestedValues) override;

    EntityStmtMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    UsesSClauseEvaluator(Argument left, Argument right);
};
