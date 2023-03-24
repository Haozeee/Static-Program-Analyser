#pragma once
#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>
#include "../ClauseEvaluator.h"
#include "../../../parser/Argument.h"
#include "ClauseArgumentsType.h"

template<typename T, typename U>
class SuchThatClauseEvaluator : public ClauseEvaluator {
 private:
    /**
     * Evaluate a such that clause in the form of clause(synonym, synonym).
     */
    void evaluateSynonymSynonym() {
        if (leftArg == rightArg) {
            evaluateEqualSynonym();
            return;
        }
        auto relationshipMap = cacheable ? getRelationshipCache(getLeftArgEntities()) : getRelationshipManager();
        if (isLeftArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, getLeftArgEntities());
        }
        if (isRightArgAmbiguous()) {
            relationshipMap = Util::mapSetIntersection(relationshipMap, getRightArgEntities());
        }
        setLeftAndRightArgResult(relationshipMap);
    }

    void evaluateValueSynonym() {
        auto relationshipStore = cacheable ? getRelationshipCache({getLeftArg()}) : getRelationshipManager();
        auto it = relationshipStore.find(getLeftArg());
        std::unordered_set<U> res {};
        if (it != relationshipStore.end()) {
            if (isRightArgAmbiguous()) {
                Util::setIntersection(getRightArgEntities(), it->second, res);
            } else {
                res = it->second;
            }
        }
        setRightArgResult(res);
    }

    void evaluateSynonymValue() {
        auto relationshipStore = cacheable ?
                getOppositeRelationshipCache({getRightArg()}) : getOppositeRelationshipManager();
        auto it = relationshipStore.find(getRightArg());
        std::unordered_set<T> res {};
        if (it != relationshipStore.end()) {
            if (isLeftArgAmbiguous()) {
                Util::setIntersection(getLeftArgEntities(), it->second, res);
            } else {
                res = it->second;
            }
        }
        setLeftArgResult(res);
    }

    void evaluateSynonymWildcard() {
        auto relationshipMap = cacheable ? getRelationshipCache(getLeftArgEntities()) : getRelationshipManager();
        if (isLeftArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, getLeftArgEntities());
        }
        std::unordered_set<T> res {};
        for (auto const& [k, v] : relationshipMap) {
            if (!v.empty()) {
                res.insert(k);
            }
        }
        setLeftArgResult(res);
    }

    void evaluateWildcardSynonym() {
        auto relationshipMap = cacheable ? getOppositeRelationshipCache(getRightArgEntities())
                : getOppositeRelationshipManager();
        if (isRightArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, getRightArgEntities());
        }
        std::unordered_set<U> res {};
        for (auto const& [k, v] : relationshipMap) {
            if (!v.empty()) {
                res.insert(k);
            }
        }
        setRightArgResult(res);
    }

    void evaluateValueValue() {
        auto relationshipStore = cacheable ? getRelationshipCache({getLeftArg()}) : getRelationshipManager();
        auto iterator = relationshipStore.find(getLeftArg());
        if (iterator == relationshipStore.end() || !iterator->second.count(getRightArg())) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateValueWildcard() {
        auto relationshipStore = cacheable ? getRelationshipCache({getLeftArg()}) : getRelationshipManager();
        auto iterator = relationshipStore.find(getLeftArg());
        if (iterator == relationshipStore.end() || iterator->second.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateWildcardValue() {
        auto relationshipStore = cacheable ?
                getOppositeRelationshipCache({getRightArg()}) : getOppositeRelationshipManager();
        auto iterator = relationshipStore.find(getRightArg());
        if (iterator == relationshipStore.end() || iterator->second.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateWildcardWildcard() {
        if (isRelationshipEmpty()) {
            clauseResultTable->setNoResults();
        }
    }

 protected:
    Argument leftArg;

    Argument rightArg;

    /**
     * Indicates if this clause is evaluated on the run by reading from a cache or if it is
     * precomputed in which case data is read from pkb directly.
     */
    bool cacheable;

    SuchThatClauseEvaluator<T, U>(Argument left, Argument right, bool cacheable = false)
            : leftArg(std::move(left)), rightArg(std::move(right)), cacheable(cacheable) {}

    virtual std::unordered_map<T, std::unordered_set<U>> getRelationshipManager() = 0;

    virtual std::unordered_map<U, std::unordered_set<T>> getOppositeRelationshipManager() = 0;

    /**
     * Before reading from a cache, need to ensure all items that is gonna be read is present in the cache.
     */
    virtual std::unordered_map<T, std::unordered_set<U>> getRelationshipCache(std::unordered_set<T> itemsToRead) {
        // By default, a relationship is not cached
        return std::unordered_map<T, std::unordered_set<U>> {};
    }

    virtual std::unordered_map<U, std::unordered_set<T>>
    getOppositeRelationshipCache(std::unordered_set<U> itemsToRead) {
        // By default, a relationship is not cached
        return std::unordered_map<U, std::unordered_set<T>> {};
    }

    /**
     * Evaluate clauses in the form of (a, a) where the 2 args refer
     * to the same identity. For most clauses, this should just return no results,
     * hence the default behaviour.
     */
    virtual void evaluateEqualSynonym() {
        clauseResultTable->setNoResults();
    }

    /**
     * Set the queryResults that are to be projected on to the left arguments in the clause result.
     * Should only be used when the left argument is a synonym.
     * @param result The result to be projected.
     */
    virtual void setLeftArgResult(std::unordered_set<T> result) = 0;

    /**
     * Set the queryResults that are to be projected on to the right arguments in the clause result.
     * Should only be used when the right argument is a synonym.
     * @param result The result to be projected.
     */
    virtual void setRightArgResult(std::unordered_set<U> result) = 0;

    /**
     * Set the queryResults that are to be projected on to the right arguments in the clause result.
     * Should only be used when the right argument is a synonym.
     * @param result The result to be projected.
     */
    virtual void setLeftAndRightArgResult(std::unordered_map<T, std::unordered_set<U>> results) = 0;

    /**
     * Get all the entities that have the same design entity as that of the left argument.
     */
    virtual std::unordered_set<T> getLeftArgEntities() = 0;

    /**
     * Get all the entities that have the same design entity as that of the right argument.
     */
    virtual std::unordered_set<U> getRightArgEntities() = 0;

    virtual T getLeftArg() = 0;

    virtual U getRightArg() = 0;

    /**
     * An argument is ambiguous if it can refer to multiple design entities. For instance, in Follows(2, s),
     * the right arg "s" can refer to a read, print, call, assign... etc statement, hence it is ambiguous.
     * Whereas, in Modifies(5, v), the right arg "v" can only refer to variables and nothing else. Hence,
     * it is not ambiguous.
     */
    virtual bool isLeftArgAmbiguous() {
        return true;
    }

    virtual bool isRightArgAmbiguous() {
        return true;
    }

    virtual bool isRelationshipEmpty() {
        return getRelationshipManager().empty();
    }

 public:
    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage_, CachePointer cache_ = nullptr) override {
        setStorageLocation(storage_, cache_);

        auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
        if (argumentType == ClauseArgumentTypes::VALUE_VALUE) {
            evaluateValueValue();
        } else if (argumentType == ClauseArgumentTypes::SYNONYM_VALUE) {
            evaluateSynonymValue();
        } else if (argumentType == ClauseArgumentTypes::VALUE_SYNONYM) {
            evaluateValueSynonym();
        } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
            evaluateSynonymSynonym();
        } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
            evaluateSynonymWildcard();
        } else if (argumentType == ClauseArgumentTypes::WILDCARD_SYNONYM) {
            evaluateWildcardSynonym();
        } else if (argumentType == ClauseArgumentTypes::VALUE_WILDCARD) {
            evaluateValueWildcard();
        } else if (argumentType == ClauseArgumentTypes::WILDCARD_VALUE) {
            evaluateWildcardValue();
        } else if (argumentType == ClauseArgumentTypes::WILDCARD_WILDCARD) {
            evaluateWildcardWildcard();
        } else {
            throw std::exception();
        }
        optimiseResults();
        return clauseResultTable;
    }
};
