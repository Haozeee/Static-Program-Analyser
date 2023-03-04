#pragma once
#include <unordered_set>
#include "StringStringClause.h"

class UsesPClause : public StringStringClause {
 public:
    UsesPClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};
