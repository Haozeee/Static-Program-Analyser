#pragma once
#include <memory>
#include "../ClauseEvaluator.h"
#include "../../../parser/Argument.h"

enum class ClauseArgumentTypes {
    NUMBER_NUMBER,
    SYNONYM_NUMBER,
    NUMBER_SYNONYM,
    SYNONYM_SYNONYM,
    NONE
};

template<typename T, typename U>
class SuchThatClauseEvaluator : public ClauseEvaluator {
 protected:
    Argument leftArg;

    Argument rightArg;

    std::shared_ptr<ClauseResult> clauseResult;

 public:
    SuchThatClauseEvaluator<T, U>(Argument left, Argument right)
            : leftArg(left), rightArg(right), clauseResult(std::make_shared<ClauseResult>()) {}

    void evaluateNumberNumber(StoragePointer storage) {
        auto relationshipStore = getRelationshipManager(storage);
        auto iterator = relationshipStore.find(stoi(leftArg.getValue()));
        auto rightValue = stoi(rightArg.getValue());
        if (iterator == relationshipStore.end() || !iterator->second.count(rightValue)) {
            clauseResult->setNoResults();
        }
    }

    void evaluateNumberSynonym(StoragePointer storage) {
        std::unordered_set<U> synonymValues = getRightArgEntities(storage);
        auto relationshipStore = getRelationshipManager(storage);
        auto it = relationshipStore.find(stoi(leftArg.getValue()));
        std::unordered_set<U> res = {};
        if (it != relationshipStore.end()) {
            PkbUtil::setIntersection(synonymValues, it->second, res);
        }
        setRightArgResult(res);
    }

    void evaluateSynonymNumber(StoragePointer storage) {
        std::unordered_set<T> synonymValues = getLeftArgEntities(storage);
        auto relationshipStore = getOppositeRelationshipManager(storage);
        auto it = relationshipStore.find(stoi(rightArg.getValue()));
        std::unordered_set<U> res = {};
        if (it != relationshipStore.end()) {
            PkbUtil::setIntersection(synonymValues, it->second, res);
        }
        setLeftArgResult(res);
    }

    void evaluateSynonymSynonym(StoragePointer storage) {
        // Maybe can make use of the opposite relationship map??
        std::unordered_map<T, std::unordered_set<U>> filteredMap = PkbUtil::filterMap(getRelationshipManager(storage),
                                                                                      getLeftArgEntities(storage));
        // Find intersection with all items of the right arg design entity
        std::pair<std::unordered_set<T>, std::unordered_set<U>> res = PkbUtil::mapSetIntersection(
                filteredMap, getRightArgEntities(storage));
        setLeftArgResult(res.first);
        setRightArgResult(res.second);
    }

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

    virtual std::unordered_map<T, std::unordered_set<U>> getRelationshipManager(StoragePointer storage) = 0;

    virtual std::unordered_map<U, std::unordered_set<T>> getOppositeRelationshipManager(StoragePointer storage) = 0;

    virtual void setLeftArgResult(std::unordered_set<T> result) = 0;

    virtual void setRightArgResult(std::unordered_set<U> result) = 0;

    virtual std::unordered_set<T> getLeftArgEntities(StoragePointer storage) = 0;

    virtual std::unordered_set<U> getRightArgEntities(StoragePointer storage) = 0;
};
