#pragma once
#include <unordered_set>
#include "StringStringClause.h"

class CallsClause : public StringStringClause {
 public:
    CallsClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};
