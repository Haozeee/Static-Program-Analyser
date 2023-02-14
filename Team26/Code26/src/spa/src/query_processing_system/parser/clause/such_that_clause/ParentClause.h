#pragma once

#include "IntStringClause.h"

class ParentClause : public IntStringClause {
 public:
    ParentClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
