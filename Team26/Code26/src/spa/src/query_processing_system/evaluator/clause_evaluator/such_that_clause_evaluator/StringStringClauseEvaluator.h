#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>

class StringStringClauseEvaluator : public SuchThatClauseEvaluator<std::string, std::string> {
 protected:
    StringStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<std::string> result) override;

    void setRightArgResult(std::unordered_set<std::string> result) override;

    std::unordered_set<std::string> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<std::string> getRightArgEntities(StoragePointer storage) override;

    void handleLeftWildcard() override;

    void handleRightWildcard() override;

    void evaluateSynonymSynonym(StoragePointer storage) override;

    void evaluateStringSynonym(StoragePointer storage);

    void evaluateStringWildCard(StoragePointer storage);

    void evaluateStringString(StoragePointer storage);

 public:
    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override;
};
