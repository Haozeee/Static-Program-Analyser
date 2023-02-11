#pragma once
#include "SuchThatClauseEvaluator.h"
#include <memory>
#include <unordered_set>

class IntIntClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 protected:
    IntIntClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<int> result) override;

    std::unordered_set<int> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<int> getRightArgEntities(StoragePointer storage) override;

    void handleLeftWildcard() override;

    void handleRightWildcard() override;

    void evaluateNumberNumber(StoragePointer storage);

    void evaluateNumberSynonym(StoragePointer storage);

    void evaluateSynonymNumber(StoragePointer storage);

    void evaluateSynonymSynonym(StoragePointer storage);

 public:
    std::shared_ptr<ClauseResult> evaluateClause(StoragePointer storage) override;
};
