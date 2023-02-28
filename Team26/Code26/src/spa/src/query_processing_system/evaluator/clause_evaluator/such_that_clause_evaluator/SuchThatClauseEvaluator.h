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
 protected:
    Argument leftArg;

    Argument rightArg;

    std::shared_ptr<ResultTable> clauseResultTable;

    SuchThatClauseEvaluator<T, U>(Argument left, Argument right)
            : leftArg(left), rightArg(right), clauseResultTable(std::make_shared<ResultTable>()) {}

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
    void setLeftAndRightArgResult(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
        clauseResultTable = ResultTable::createTableFromMap(results, leftArg.getValue(), rightArg.getValue());
    }

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
     * the right arg "s" can refer to a read, print, call or assign statement, hence it is ambiguous.
     * Whereas, in Modifies(5, v), the right arg "v" can only refer to variables and nothing else. Hence,
     * it is not ambiguous.
     */
    virtual bool isLeftArgAmbiguous() = 0;

    virtual bool isRightArgAmbiguous() = 0;

    virtual void handleLeftWildcard() = 0;

    virtual void handleRightWildcard() = 0;

    void handleWildcards() {
        if (leftArg.getArgumentType() == ArgumentType::WILDCARD) {
            handleLeftWildcard();
        } else if (rightArg.getArgumentType() == ArgumentType::WILDCARD) {
            handleRightWildcard();
        }
    }

    /**
     * Evaluate a such that clause in the form of clause(synonym, synonym).
     * This is a valid evaluation parameter for all such that clauses,
     * hence it exists in the parent class.
     */
    virtual void evaluateSynonymSynonym(StoragePointer storage) = 0;

    void evaluateSynonymWildcard(StoragePointer storage) {
        handleRightWildcard();
        evaluateSynonymSynonym(storage);
        // Remove wildcard placeholder
        clauseResultTable = ResultTable::createSingleColumnTable(
                leftArg.getValue(), clauseResultTable->getColumnValues(leftArg.getValue()));
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
        if (iterator == relationshipStore.end() || !iterator->second.empty()) {
            clauseResultTable->setNoResults();
        }
    }

    void evaluateWildcardValue(StoragePointer storage) {
        auto relationshipStore = getOppositeRelationshipManager(storage);
        auto iterator = relationshipStore.find(getRightArg());
        if (iterator == relationshipStore.end() || !iterator->second.empty()) {
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
};
