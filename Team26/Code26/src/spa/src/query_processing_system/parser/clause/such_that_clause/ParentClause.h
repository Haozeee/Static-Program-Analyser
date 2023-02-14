#pragma once

#include "SuchThatClause.h"

class ParentClause : public SuchThatClause {
 public:
    ParentClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    ValidArgumentType getValidArgumentType() override;

    ValidDesignEntity getValidDesignEntity() override;
};
