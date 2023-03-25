#pragma once

#include "IntStringClauseEvaluator.h"
#include <string>

class ModifiesSClauseEvaluator : public IntStringClauseEvaluator {
 public:
    ModifiesSClauseEvaluator(Argument left, Argument right);

    StmtEntityMap getRelationshipManager() override;

    EntityStmtMap getOppositeRelationshipManager() override;
};
