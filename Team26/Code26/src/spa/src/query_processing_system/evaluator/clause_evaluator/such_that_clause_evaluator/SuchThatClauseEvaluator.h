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
    NONE
};

template<typename T, typename U>
class SuchThatClauseEvaluator : public ClauseEvaluator {
 protected:
    Argument leftArg;

    Argument rightArg;

    std::shared_ptr<ClauseResult> clauseResult;

    virtual std::unordered_map<T, std::unordered_set<U>> getRelationshipManager(StoragePointer storage) = 0;

    virtual std::unordered_map<U, std::unordered_set<T>> getOppositeRelationshipManager(StoragePointer storage) = 0;

    /**
     * Set the results that are to be projected on to the left arguments in the clause result.
     * Should only be used when the left argument is a synonym.
     * @param result The result to be projected.
     */
    virtual void setLeftArgResult(std::unordered_set<T> result) = 0;

    /**
     * Set the results that are to be projected on to the right arguments in the clause result.
     * Should only be used when the right argument is a synonym.
     * @param result The result to be projected.
     */
    virtual void setRightArgResult(std::unordered_set<U> result) = 0;

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
public:
    SuchThatClauseEvaluator<T, U>(Argument left, Argument right)
            : leftArg(left), rightArg(right), clauseResult(std::make_shared<ClauseResult>()) {}

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
        } else {
            return ClauseArgumentTypes::NONE;
        }
    }
};
