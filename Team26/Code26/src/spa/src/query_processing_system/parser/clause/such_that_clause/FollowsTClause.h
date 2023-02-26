#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class FollowsTClause : public IntIntClause {
 public:
    FollowsTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidLeftDesignEntity() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};
