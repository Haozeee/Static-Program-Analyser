#pragma once

#include "IntIntClause.h"

class ParentClause : public IntIntClause {
 public:
    ParentClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
