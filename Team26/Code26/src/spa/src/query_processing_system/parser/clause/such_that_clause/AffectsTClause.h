#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class AffectsTClause : public IntIntClause {
 public:
    AffectsTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
