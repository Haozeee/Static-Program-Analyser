#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class AffectsTClause : public IntIntClause {
 public:
    AffectsTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidLeftDesignEntity() override;

    std::unordered_set<DesignEntity> getValidRightDesignEntity() override;
};