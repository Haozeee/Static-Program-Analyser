#pragma once
#include "IntIntClause.h"

class FollowsClause : public IntIntClause {
 public:
    FollowsClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidLeftDesignEntity() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};
