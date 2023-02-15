#pragma once

#include "IntIntClause.h"

/**
 * Not needed for milestone 1.
 */
class UsesPClause : public IntIntClause {
 public:
    UsesPClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
