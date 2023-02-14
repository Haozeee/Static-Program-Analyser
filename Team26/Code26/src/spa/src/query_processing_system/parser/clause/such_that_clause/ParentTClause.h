#pragma once

#include "IntStringClause.h"

class ParentTClause : public IntStringClause {
 public:
    ParentTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
