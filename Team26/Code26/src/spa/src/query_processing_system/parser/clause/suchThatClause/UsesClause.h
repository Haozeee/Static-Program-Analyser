#pragma once
#include "SuchThatClause.h"

class UsesClause : public SuchThatClause {
public:
    ClauseEvaluator* getClauseEvaluator() override;
};

