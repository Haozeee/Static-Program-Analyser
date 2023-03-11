#pragma once
#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "IntIntClauseEvaluator.h"
#include "cache.h"

class CacheableSuchThatClauseEvaluator : IntIntClauseEvaluator {
 protected:
    CachePointer cache;

    CacheableSuchThatClauseEvaluator(Argument left, Argument right);

    void evaluateValueValue() override;

    void evaluateSynonymValue() override;

    void evaluateValueSynonym() override;

    void evaluateSynonymSynonym() override;

    void evaluateSynonymWildcard() override;

    void evaluateWildcardSynonym() override;

    void evaluateValueWildcard() override;

    void evaluateWildcardValue() override;

    void evaluateWildcardWildcard() override;

    std::unordered_set<int> getLeftArgEntities() override;

    std::unordered_set<int> getRightArgEntities() override;

    int getLeftArg() override;

    int getRightArg() override;


    virtual std::unordered_set<int> getValueFromRelationshipCache(int value) = 0;

    virtual std::unordered_set<int> getValueFromReverseRelationshipCache(int value) = 0;

    void setStorageLocation(StoragePointer storage_, CachePointer cache_) override;
};
