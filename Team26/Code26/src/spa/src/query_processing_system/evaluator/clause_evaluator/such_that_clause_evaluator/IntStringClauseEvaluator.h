#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

class IntStringClauseEvaluator : public SuchThatClauseEvaluator<int, std::string> {
 private:
    std::unordered_set<std::string> evaluateNumberSynonymHelper(StoragePointer storage, int stmtNumber);

 protected:
    IntStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<std::string> result) override;

    void setLeftAndRightArgResult(std::unordered_map<std::string, std::unordered_set<std::string>> results) override;

    std::unordered_set<int> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<std::string> getRightArgEntities(StoragePointer storage) override;

    void handleLeftWildcard() override;

    void handleRightWildcard() override;

    void evaluateSynonymSynonym(StoragePointer storage) override;

    void evaluateNumberSynonym(StoragePointer storage);

    void evaluateSynonymString(StoragePointer storage);

    void evaluateNumberString(StoragePointer storage);

    void evaluateNumberWildcard(StoragePointer storage);

    virtual std::unordered_map<int, std::unordered_set<int>> getChildrenRelationMap(StoragePointer storage);

 public:
    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override;
};
