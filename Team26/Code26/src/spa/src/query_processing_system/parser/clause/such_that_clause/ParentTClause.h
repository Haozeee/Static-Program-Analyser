#pragma once

#include "SuchThatClause.h"

class ParentTClause : public SuchThatClause {
public:
    ParentTClause(Argument leftArg, Argument rightArg);

    ClauseEvaluator* getClauseEvaluator() override;
};
