#pragma once

#include "SuchThatClause.h"

class ModifiesSClause : public SuchThatClause {
 public:
    ModifiesSClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
