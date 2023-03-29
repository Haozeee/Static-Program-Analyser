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
        auto interestedValues = getLeftArgEntities();
        auto relationshipMap = getRelationshipMap(interestedValues);
        if (isLeftArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, interestedValues);
        }
        if (isRightArgAmbiguous()) {
            relationshipMap = Util::mapSetIntersection(relationshipMap, getRightArgEntities());
        }
        setLeftAndRightArgResult(relationshipMap);
    }

    void evaluateValueSynonym() {
        std::unordered_set<T> interestedValues {getLeftArg()};
        auto relationshipStore = getRelationshipMap(interestedValues);
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
        std::unordered_set<U> interestedValues {getRightArg()};
        auto relationshipStore = getOppositeRelationshipMap(interestedValues);
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
        auto interestedValues = getLeftArgEntities();
        auto relationshipMap = getRelationshipMap(interestedValues);
        if (isLeftArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, interestedValues);
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
        auto interestedValues = getRightArgEntities();
        auto relationshipMap = getOppositeRelationshipMap(interestedValues);
        if (isRightArgAmbiguous()) {
            relationshipMap = Util::filterMap(relationshipMap, interestedValues);
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
        std::unordered_set<T> interestedValues {getLeftArg()};
        auto relationshipStore = getRelationshipMap(interestedValues);
        auto iterator = relationshipStore.find(getLeftArg());
        if (iterator == relationshipStore.end() || !iterator->second.count(getRightArg())) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateValueWildcard() {
        std::unordered_set<T> interestedValues {getLeftArg()};
        auto relationshipStore = getRelationshipMap(interestedValues);
        auto iterator = relationshipStore.find(getLeftArg());
        if (iterator == relationshipStore.end() || iterator->second.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateWildcardValue() {
        std::unordered_set<U> interestedValues {getRightArg()};
        auto relationshipStore = getOppositeRelationshipMap(interestedValues);
        auto iterator = relationshipStore.find(getRightArg());
        if (iterator == relationshipStore.end() || iterator->second.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateWildcardWildcard() {
        if (isEmptyRelation()) {
            clauseResultTable->setNoResults();
        }
    }

 protected:
    Argument leftArg;

    Argument rightArg;

    SuchThatClauseEvaluator<T, U>(Argument left, Argument right)
        : leftArg(std::move(left)), rightArg(std::move(right)) {}

    virtual std::unordered_map<T, std::unordered_set<U>>
    getRelationshipMap(std::unordered_set<T> &interestedValues) = 0;

    virtual std::unordered_map<U, std::unordered_set<T>>
    getOppositeRelationshipMap(std::unordered_set<U> &interestedValues) = 0;

    virtual bool isEmptyRelation() = 0;

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
     * @param result The result to be projected.
     */
    virtual void setLeftArgResult(std::unordered_set<T> result) = 0;

    /**
     * Set the queryResults that are to be projected on to the right arguments in the clause result.
     * @param result The result to be projected.
     */
    virtual void setRightArgResult(std::unordered_set<U> result) = 0;

    /**
     * Set the queryResults that are to be projected on to the right arguments in the clause result.
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
    virtual bool isLeftArgAmbiguous() = 0;

    virtual bool isRightArgAmbiguous() = 0;

 public:
    std::shared_ptr<ResultTable> evaluateClause(ProgrammeStore storage_) override {
        setStorageLocation(storage_);
        auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());

        std::unordered_map<ClauseArgumentTypes, std::function<void(void)>> evalMap {
                {ClauseArgumentTypes::SYNONYM_SYNONYM, [this](){ evaluateSynonymSynonym(); }},
                {ClauseArgumentTypes::SYNONYM_VALUE, [this](){ evaluateSynonymValue(); }},
                {ClauseArgumentTypes::VALUE_SYNONYM, [this](){ evaluateValueSynonym(); }},
                {ClauseArgumentTypes::SYNONYM_WILDCARD, [this](){ evaluateSynonymWildcard(); }},
                {ClauseArgumentTypes::WILDCARD_SYNONYM, [this](){ evaluateWildcardSynonym(); }},
                {ClauseArgumentTypes::VALUE_WILDCARD, [this](){ evaluateValueWildcard(); }},
                {ClauseArgumentTypes::WILDCARD_VALUE, [this](){ evaluateWildcardValue(); }},
                {ClauseArgumentTypes::VALUE_VALUE, [this](){ evaluateValueValue(); }},
                {ClauseArgumentTypes::WILDCARD_WILDCARD, [this](){ evaluateWildcardWildcard(); }}
        };

        auto it = evalMap.find(argumentType);
        if (it != evalMap.end()) {
            it->second();
        }
        optimiseResults();

        return clauseResultTable;
    }
};
