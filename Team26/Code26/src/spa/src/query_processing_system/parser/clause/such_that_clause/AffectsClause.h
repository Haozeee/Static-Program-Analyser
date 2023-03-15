#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class AffectsClause : public IntIntClause {
 public:
    AffectsClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
