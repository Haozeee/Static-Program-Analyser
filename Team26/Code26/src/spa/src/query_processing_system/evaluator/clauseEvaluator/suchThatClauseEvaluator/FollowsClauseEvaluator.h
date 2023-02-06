#pragma once
#include "SuchThatClauseEvaluator.h"
#include <memory>

class FollowsClauseEvaluator : public SuchThatClauseEvaluator {
 private:
    void evaluateNumberNumber(std::shared_ptr<ReadOnlyStorage> storage);

    void evaluateNumberSynonym(std::shared_ptr<ReadOnlyStorage> storage);

 public:
    FollowsClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
