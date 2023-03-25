#pragma once

#include "IntStringClauseEvaluator.h"
#include <string>

class UsesSClauseEvaluator : public IntStringClauseEvaluator {
 public:
    UsesSClauseEvaluator(Argument left, Argument right);

    StmtEntityMap getRelationshipManager() override;

    EntityStmtMap getOppositeRelationshipManager() override;
};
