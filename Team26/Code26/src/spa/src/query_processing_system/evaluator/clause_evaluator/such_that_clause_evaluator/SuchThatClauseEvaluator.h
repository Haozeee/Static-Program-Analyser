#pragma once
#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include "../ClauseEvaluator.h"
#include "../../../parser/Argument.h"

enum class ClauseArgumentTypes {
    NUMBER_NUMBER,
    SYNONYM_NUMBER,
    NUMBER_SYNONYM,
    SYNONYM_SYNONYM,
    SYNONYM_STRING,
    NUMBER_STRING,
    WILDCARD_NUMBER,
    NUMBER_WILDCARD,
    SYNONYM_WILDCARD,
    WILDCARD_SYNONYM,
    WILDCARD_WILDCARD,
    WILDCARD_STRING,
    NONE
};

template<typename T, typename U>
class SuchThatClauseEvaluator : public ClauseEvaluator {
 protected:
    Argument leftArg;

    Argument rightArg;

    std::shared_ptr<ResultTable> clauseResultTable;

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
        handleRightWildcard();
        evaluateSynonymSynonym(storage);
        // Remove wildcard placeholder
        clauseResultTable = ResultTable::createSingleColumnTable(
                rightArg.getValue(), clauseResultTable->getColumnValues(rightArg.getValue()));
    }

    void evaluateSynonymWildcard(StoragePointer storage) {
        handleLeftWildcard();
        evaluateSynonymSynonym(storage);
        // Remove wildcard placeholder
        clauseResultTable = ResultTable::createSingleColumnTable(
                leftArg.getValue(), clauseResultTable->getColumnValues(leftArg.getValue()));
    }

 public:
    SuchThatClauseEvaluator<T, U>(Argument left, Argument right)
            : leftArg(left), rightArg(right), clauseResultTable(std::make_shared<ResultTable>()) {}

    ClauseArgumentTypes getClauseArgumentTypes() {
        auto l = leftArg.getArgumentType();
        auto r = rightArg.getArgumentType();
        if (l == ArgumentType::NUMBER && r == ArgumentType::NUMBER) {
            return ClauseArgumentTypes::NUMBER_NUMBER;
        } else if (l == ArgumentType::SYNONYM && r == ArgumentType::NUMBER) {
            return ClauseArgumentTypes::SYNONYM_NUMBER;
        } else if (l == ArgumentType::NUMBER && r == ArgumentType::SYNONYM) {
            return ClauseArgumentTypes::NUMBER_SYNONYM;
        } else if (l == ArgumentType::SYNONYM && r == ArgumentType::SYNONYM) {
            return ClauseArgumentTypes::SYNONYM_SYNONYM;
        } else if (l == ArgumentType::NUMBER && r == ArgumentType::CHARACTERSTRING) {
            return ClauseArgumentTypes::NUMBER_STRING;
        } else if (l == ArgumentType::SYNONYM && r == ArgumentType::CHARACTERSTRING) {
            return ClauseArgumentTypes::SYNONYM_STRING;
        } else {
            return ClauseArgumentTypes::NONE;
        }
    }
};
