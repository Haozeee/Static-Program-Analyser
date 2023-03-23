#pragma once
#include "../../evaluator/clause_evaluator/ClauseEvaluator.h"

class Clause {
 public:
    /**
     * Get the evaluator which will be used to evaluate a particular clause.
     * @return The clause evaluator object.
     */
    virtual ClauseEvaluator* getClauseEvaluator() = 0;

    /**
     * For each clause, get a score that will be used to get the order of clause
     * evaluation. The lower the points, the more likely it is to be sorted first.
     * @return The points to be used for sorting.
     */
    virtual int getOptimisationPoints() = 0;
};
