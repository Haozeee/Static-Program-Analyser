#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class NextClause : public IntIntClause {
 public:
    NextClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
