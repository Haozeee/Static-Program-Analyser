#pragma once
#include "../../evaluator/clauseEvaluator/ClauseEvaluator.h"

class Clause {
 public:
    /**
     * Get the evaluator which will be used to evaluate a particular clause.
     * @return The clause evaluator object.
     */
    virtual ClauseEvaluator* getClauseEvaluator() = 0;
};
