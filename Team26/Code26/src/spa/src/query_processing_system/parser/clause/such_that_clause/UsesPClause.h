#pragma once

#include "SuchThatClause.h"

class UsesPClause : public SuchThatClause {
 public:
    UsesPClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    ValidArgumentType getValidArgumentType() override;

    ValidDesignEntity getValidDesignEntity() override;
};
