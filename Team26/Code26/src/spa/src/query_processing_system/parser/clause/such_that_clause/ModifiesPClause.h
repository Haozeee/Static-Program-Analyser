#pragma once
#include <unordered_set>
#include "StringStringClause.h"

class ModifiesPClause : public StringStringClause {
 public:
    ModifiesPClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};
