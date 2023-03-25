#pragma once

#include "IntStringClauseEvaluator.h"
#include <string>

class ModifiesSClauseEvaluator : public IntStringClauseEvaluator {
 protected:
    StmtEntityMap getRelationshipMap(StmtSet &interestedValues) override;

    EntityStmtMap getOppositeRelationshipMap(EntitySet &interestedValues) override;

    bool isEmptyRelation() override;

 public:
    ModifiesSClauseEvaluator(Argument left, Argument right);
};
