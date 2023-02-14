#pragma once
#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>
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
    virtual void setLeftAndRightArgResult(std::unordered_set<T> resultLeft, std::unordered_set<U> resultRight) = 0;

    /**
     * Get all the entities that have the same design entity as that of the left argument.
     */
    virtual std::unordered_set<T> getLeftArgEntities(StoragePointer storage) = 0;

    /**
     * Get all the entities that have the same design entity as that of the right argument.
     */
    virtual std::unordered_set<U> getRightArgEntities(StoragePointer storage) = 0;

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
     * This is a valid evaluation parameter for all such that clauses,
     * hence it exists in the parent class.
     */
    virtual void evaluateSynonymSynonym(StoragePointer storage) = 0;

    void evaluateWildcardSynonym(StoragePointer storage) {
        handleLeftWildcard();
        evaluateSynonymSynonym(storage);
        // Remove wildcard placeholder
        clauseResultTable = ResultTable::createSingleColumnTable(
                rightArg.getValue(), clauseResultTable->getColumnValues(rightArg.getValue()));
    }

    void evaluateSynonymWildcard(StoragePointer storage) {
        handleRightWildcard();
        evaluateSynonymSynonym(storage);
        // Remove wildcard placeholder
        clauseResultTable = ResultTable::createSingleColumnTable(
                leftArg.getValue(), clauseResultTable->getColumnValues(leftArg.getValue()));
    }
};
