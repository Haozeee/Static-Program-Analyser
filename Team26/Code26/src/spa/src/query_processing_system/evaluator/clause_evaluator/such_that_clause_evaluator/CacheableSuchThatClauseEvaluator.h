#pragma once
#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "SuchThatClauseEvaluator.h"
#include "cache.h"

class CacheableSuchThatClauseEvaluator : SuchThatClauseEvaluator<int, int> {
 private:
    CachePointer cache;

    void evaluateValueValue() override;

    void evaluateSynonymValue() override;

    void evaluateValueSynonym() override;

    void evaluateSynonymSynonym() override;

    void evaluateSynonymWildcard() override;

    void evaluateWildcardSynonym() override;

    void evaluateValueWildcard() override;

    void evaluateWildcardValue() override;

    void evaluateWildcardWildcard() override;

    virtual CacheableGraph getRelationshipCache() = 0;

    virtual CacheableGraph getReverseRelationshipCache() = 0;

 protected:
    CacheableSuchThatClauseEvaluator(Argument left, Argument right);

    void setStorageLocation(StoragePointer storage_, CachePointer cache_) override;
};
