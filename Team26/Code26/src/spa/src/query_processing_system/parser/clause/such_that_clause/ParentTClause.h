#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class ParentTClause : public IntIntClause {
 public:
    ParentTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
