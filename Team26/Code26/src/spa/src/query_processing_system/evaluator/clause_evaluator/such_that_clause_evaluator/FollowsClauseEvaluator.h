#pragma once
#include <memory>
#include "SuchThatClauseEvaluator.h"

class FollowsClauseEvaluator : public SuchThatClauseEvaluator {
 private:
    void evaluateNumberNumber(std::shared_ptr<ReadOnlyStorage> storage);

    void evaluateNumberSynonym(std::shared_ptr<ReadOnlyStorage> storage);

    void evaluateSynonymNumber(std::shared_ptr<ReadOnlyStorage> storage);

    void evaluateSynonymSynonym(std::shared_ptr<ReadOnlyStorage> storage);
 public:
    FollowsClauseEvaluator(Argument left, Argument right);

    std::shared_ptr<ClauseResult> evaluateClause(std::shared_ptr<ReadOnlyStorage> storage) override;
};
