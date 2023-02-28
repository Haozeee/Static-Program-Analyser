#pragma once
#include <unordered_set>
#include "IntIntClause.h"

class AffectsClause : public IntIntClause {
 public:
    AffectsClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;

    std::unordered_set<DesignEntity> getValidLeftDesignEntity() override;
};
