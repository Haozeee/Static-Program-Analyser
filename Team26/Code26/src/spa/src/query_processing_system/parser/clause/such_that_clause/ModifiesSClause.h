#pragma once

#include "IntStringClause.h"

class ModifiesSClause : public IntStringClause {
 public:
    ModifiesSClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
