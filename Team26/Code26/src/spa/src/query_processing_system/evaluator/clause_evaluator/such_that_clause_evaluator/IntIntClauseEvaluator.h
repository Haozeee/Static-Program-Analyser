#pragma once
#include "SuchThatClauseEvaluator.h"
#include <memory>
#include <unordered_set>

class IntIntClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 protected:
    IntIntClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<int> result) override;

    void setLeftAndRightArgResult(std::unordered_set<int> resultLeft, std::unordered_set<int> resultRight) override;

    std::unordered_set<int> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<int> getRightArgEntities(StoragePointer storage) override;

    void handleLeftWildcard() override;

    void handleRightWildcard() override;

    void evaluateSynonymSynonym(StoragePointer storage) override;

    void evaluateNumberNumber(StoragePointer storage);

    void evaluateNumberSynonym(StoragePointer storage);

    void evaluateSynonymNumber(StoragePointer storage);

    void evaluateNumberWithWildcard(StoragePointer storage);

    void evaluateWildcardSynonym(StoragePointer storage);

 public:
    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override;
};
