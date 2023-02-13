#pragma once

#include "SuchThatClause.h"

class ModifiesPClause : public SuchThatClause {
 public:
    ModifiesPClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    ValidArgumentType getValidArgumentType() override;

    ValidDesignEntity getValidDesignEntity() override;
};
