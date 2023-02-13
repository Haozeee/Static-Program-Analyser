#pragma once

#include "SuchThatClause.h"

class FollowsTClause : public SuchThatClause {
 public:
    FollowsTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    ValidArgumentType getValidArgumentType() override;

    ValidDesignEntity getValidDesignEntity() override;
};
