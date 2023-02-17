#pragma once
#include "SuchThatClauseEvaluator.h"
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <string>

class IntIntClauseEvaluator : public SuchThatClauseEvaluator<int, int> {
 protected:
    IntIntClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<int> result) override;

    void setLeftAndRightArgResult(std::unordered_map<std::string, std::unordered_set<std::string>> results) override;

    std::unordered_set<int> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<int> getRightArgEntities(StoragePointer storage) override;

    void handleLeftWildcard() override;

    void handleRightWildcard() override;

    void evaluateSynonymSynonym(StoragePointer storage) override;

    /**
    * Evaluate a such that clause in the form of clause(int, int).
    */
    void evaluateNumberNumber(StoragePointer storage);

    /**
    * Evaluate a such that clause in the form of clause(int, synonym).
    */
    void evaluateNumberSynonym(StoragePointer storage);

    /**
    * Evaluate a such that clause in the form of clause(synonym, int).
    */
    void evaluateSynonymNumber(StoragePointer storage);

    /**
    * Evaluate a such that clause in the form of clause(int, _) or clause (_, int).
    */
    void evaluateNumberWithWildcard(StoragePointer storage);

    /**
    * Evaluate a such that clause in the form of clause(_, synonym).
    */
    void evaluateWildcardSynonym(StoragePointer storage);

    /**
    * Evaluate a such that clause in the form of clause(_,_).
    */
    void evaluateWildcardWildcard(StoragePointer storage);

 public:
    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override;
};
