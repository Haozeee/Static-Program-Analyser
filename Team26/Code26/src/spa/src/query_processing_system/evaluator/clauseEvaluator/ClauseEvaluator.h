#pragma once

class ClauseEvaluator {
public:
    virtual ~ClauseEvaluator() = default;
    virtual bool evaluateClause() = 0;
};
