#pragma once

#include "IntIntClause.h"

class ParentTClause : public IntIntClause {
 public:
    ParentTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
