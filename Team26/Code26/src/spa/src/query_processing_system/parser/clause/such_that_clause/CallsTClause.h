#pragma once
#include <unordered_set>
#include "StringStringClause.h"

class CallsTClause : public StringStringClause {
 public:
    CallsTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};
