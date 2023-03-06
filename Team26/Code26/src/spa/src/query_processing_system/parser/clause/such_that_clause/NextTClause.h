#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class NextTClause : public IntIntClause {
 public:
    NextTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
