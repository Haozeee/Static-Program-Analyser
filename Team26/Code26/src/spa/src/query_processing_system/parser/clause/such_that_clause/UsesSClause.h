#pragma once

#include "IntStringClause.h"

class UsesSClause : public IntStringClause {
 public:
    UsesSClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};

