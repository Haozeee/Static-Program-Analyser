#pragma once

#include "IntIntClause.h"

/**
 * Not needed for milestone 1.
 */
class ModifiesPClause : public IntIntClause {
 public:
    ModifiesPClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
