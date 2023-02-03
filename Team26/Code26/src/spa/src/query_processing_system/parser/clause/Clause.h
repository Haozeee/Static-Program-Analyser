#pragma once
#include "../../evaluator/clauseEvaluator/ClauseEvaluator.h"

class Clause {
public:
    virtual ClauseEvaluator* getClauseEvaluator() = 0;
};
