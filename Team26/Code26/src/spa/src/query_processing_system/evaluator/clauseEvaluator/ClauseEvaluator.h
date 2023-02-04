#pragma once

class ClauseEvaluator {
 public:
    virtual ~ClauseEvaluator() = default;
    /**
     * Evaluate the clause.
     * @return True if clause has been evaluated successfully.
     */
    virtual bool evaluateClause() = 0;
};
