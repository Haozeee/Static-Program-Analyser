#pragma once
#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "../ClauseEvaluator.h"
#include "../../../parser/Argument.h"
#include "ClauseArgumentsType.h"

template<typename T, typename U>
class SuchThatClauseEvaluator : public ClauseEvaluator {
 private:
    /**
     * Evaluate a such that clause in the form of clause(synonym, synonym).
     */
    void evaluateSynonymSynonym(StoragePointer storage) {
        if (leftArg == rightArg) {
            clauseResultTable->setNoResults();
            return;
        }
        // Set initial empty results
        std::unordered_map<T, std::unordered_set<U>> res;
        auto relationshipMap = getRelationshipManager(storage);
        if (isLeftArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, getLeftArgEntities(storage));
        }
        if (isRightArgAmbiguous()) {
            relationshipMap = Util::mapSetIntersection(relationshipMap, getRightArgEntities(storage));
        }
        setLeftAndRightArgResult(relationshipMap);
    }

    void evaluateValueSynonym(StoragePointer storage) {
        auto relationshipStore = getRelationshipManager(storage);
        auto it = relationshipStore.find(getLeftArg());
        std::unordered_set<U> res {};
        if (it != relationshipStore.end()) {
            if (isRightArgAmbiguous()) {
                Util::setIntersection(getRightArgEntities(storage), it->second, res);
            } else {
                res = it->second;
            }
        }
        setRightArgResult(res);
    }

    void evaluateSynonymValue(StoragePointer storage) {
        auto relationshipStore = getOppositeRelationshipManager(storage);
        auto it = relationshipStore.find(getRightArg());
        std::unordered_set<T> res {};
        if (it != relationshipStore.end()) {
            if (isLeftArgAmbiguous()) {
                Util::setIntersection(getLeftArgEntities(storage), it->second, res);
            } else {
                res = it->second;
            }
        }
        setLeftArgResult(res);
    }

    void evaluateSynonymWildcard(StoragePointer storage) {
        auto relationshipMap = getRelationshipManager(storage);
        if (isLeftArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, getLeftArgEntities(storage));
        }
        std::unordered_set<T> res {};
        for (auto const& [k, v] : relationshipMap) {
            if (!v.empty()) {
                res.insert(k);
            }
        }
        setLeftArgResult(res);
    }

    void evaluateWildcardSynonym(StoragePointer storage) {
        handleLeftWildcard();
        evaluateSynonymSynonym(storage);
        // Remove wildcard placeholder
        clauseResultTable = ResultTable::createSingleColumnTable(
                rightArg.getValue(), clauseResultTable->getColumnValues(rightArg.getValue()));
    }

    void evaluateValueValue(StoragePointer storage) {
        auto relationshipStore = getRelationshipManager(storage);
        auto iterator = relationshipStore.find(getLeftArg());
        if (iterator == relationshipStore.end() || !iterator->second.count(getRightArg())) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateValueWildcard(StoragePointer storage) {
        auto relationshipStore = getRelationshipManager(storage);
        auto iterator = relationshipStore.find(getLeftArg());
        if (iterator == relationshipStore.end() || iterator->second.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateWildcardValue(StoragePointer storage) {
        auto relationshipStore = getOppositeRelationshipManager(storage);
        auto iterator = relationshipStore.find(getRightArg());
        if (iterator == relationshipStore.end() || iterator->second.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateWildcardWildcard(StoragePointer storage) {
        auto relationshipStore = getRelationshipManager(storage);
        if (relationshipStore.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    /**
     * Checks if the result of this such that clause equates to false. The such that clause
     * is false when there are columns but no row in the ResultTable. If the such that clause is
     * false, we can set the clause results as false and we do not evaluate any other clauses in
     * the query.
     */
    void optimiseResults() {
        if (!clauseResultTable->getColumnsNames().empty() && clauseResultTable->getNumberOfRows() == 0) {
            clauseResultTable->setNoResults();
        }
    }

 protected:
    Argument leftArg;

    Argument rightArg;

    SuchThatClauseEvaluator<T, U>(Argument left, Argument right)
            : leftArg(left), rightArg(right) {}

    virtual std::unordered_map<T, std::unordered_set<U>> getRelationshipManager(StoragePointer storage) = 0;

    virtual std::unordered_map<U, std::unordered_set<T>> getOppositeRelationshipManager(StoragePointer storage) = 0;

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
    virtual std::unordered_set<T> getLeftArgEntities(StoragePointer storage) = 0;

    /**
     * Get all the entities that have the same design entity as that of the right argument.
     */
    virtual std::unordered_set<U> getRightArgEntities(StoragePointer storage) = 0;

    virtual T getLeftArg() = 0;

    virtual U getRightArg() = 0;

    /**
     * An argument is ambiguous if it can refer to multiple design entities. For instance, in Follows(2, s),
     * the right arg "s" can refer to a read, print, call, assign... etc statement, hence it is ambiguous.
     * Whereas, in Modifies(5, v), the right arg "v" can only refer to variables and nothing else. Hence,
     * it is not ambiguous.
     */
    virtual bool isLeftArgAmbiguous() = 0;

    virtual bool isRightArgAmbiguous() = 0;

    virtual void handleLeftWildcard() = 0;

    virtual void handleRightWildcard() = 0;

 public:
    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override {
        auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
        if (argumentType == ClauseArgumentTypes::VALUE_VALUE) {
            evaluateValueValue(storage);
        } else if (argumentType == ClauseArgumentTypes::SYNONYM_VALUE) {
            evaluateSynonymValue(storage);
        } else if (argumentType == ClauseArgumentTypes::VALUE_SYNONYM) {
            evaluateValueSynonym(storage);
        } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
            evaluateSynonymSynonym(storage);
        } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
            evaluateSynonymWildcard(storage);
        } else if (argumentType == ClauseArgumentTypes::WILDCARD_SYNONYM) {
            evaluateWildcardSynonym(storage);
        } else if (argumentType == ClauseArgumentTypes::VALUE_WILDCARD) {
            evaluateValueWildcard(storage);
        } else if (argumentType == ClauseArgumentTypes::WILDCARD_VALUE) {
            evaluateWildcardValue(storage);
        } else if (argumentType == ClauseArgumentTypes::WILDCARD_WILDCARD) {
            evaluateWildcardWildcard(storage);
        } else {
            throw std::exception();
        }
        optimiseResults();
        return clauseResultTable;
    }
};
