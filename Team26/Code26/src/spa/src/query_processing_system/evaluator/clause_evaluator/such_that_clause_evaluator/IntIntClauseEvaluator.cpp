#include "IntIntClauseEvaluator.h"

IntIntClauseEvaluator::IntIntClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, int>(left, right) {}

std::shared_ptr<ClauseResult> IntIntClauseEvaluator::evaluateClause(StoragePointer storage) {
    ClauseArgumentTypes argumentType = getClauseArgumentTypes();
    switch (argumentType) {
        case ClauseArgumentTypes::NUMBER_NUMBER:
            evaluateNumberNumber(storage);
            break;
        case ClauseArgumentTypes::SYNONYM_NUMBER:
            evaluateSynonymNumber(storage);
            break;
        case ClauseArgumentTypes::NUMBER_SYNONYM:
            evaluateNumberSynonym(storage);
            break;
        case ClauseArgumentTypes::SYNONYM_SYNONYM:
            std::cout << "Synonym sybn\n";
            evaluateSynonymSynonym(storage);
            break;
        case ClauseArgumentTypes::NONE:
            std::cout << "None\n";
            throw std::exception();
    }
    return clauseResult;
}

/**
     * Evaluate a such that clause in the form of clause(int, int)
     */
void IntIntClauseEvaluator::evaluateNumberNumber(StoragePointer storage) {
    auto relationshipStore = getRelationshipManager(storage);
    auto iterator = relationshipStore.find(stoi(leftArg.getValue()));
    auto rightValue = stoi(rightArg.getValue());
    if (iterator == relationshipStore.end() || !iterator->second.count(rightValue)) {
        clauseResult->setNoResults();
    }
}

/**
 * Evaluate a such that clause in the form of clause(int, synonym)
 */
void IntIntClauseEvaluator::evaluateNumberSynonym(StoragePointer storage) {
    auto synonymValues = getRightArgEntities(storage);
    auto relationshipStore = getRelationshipManager(storage);
    auto it = relationshipStore.find(stoi(leftArg.getValue()));
    std::unordered_set<int> res = {};
    if (it != relationshipStore.end()) {
        PkbUtil::setIntersection(synonymValues, it->second, res);
    }
    setRightArgResult(res);
}

/**
 * Evaluate a such that clause in the form of clause(synonym, int)
 */
void IntIntClauseEvaluator::evaluateSynonymNumber(StoragePointer storage) {
    auto synonymValues = getLeftArgEntities(storage);
    auto relationshipStore = getOppositeRelationshipManager(storage);
    auto it = relationshipStore.find(stoi(rightArg.getValue()));
    std::unordered_set<int> res = {};
    if (it != relationshipStore.end()) {
        PkbUtil::setIntersection(synonymValues, it->second, res);
    }
    setLeftArgResult(res);
}

/**
 * Evaluate a such that clause in the form of clause(synonym, synonym)
 */
void IntIntClauseEvaluator::evaluateSynonymSynonym(StoragePointer storage) {
    // Maybe can make use of the opposite relationship map??
    auto filteredMap = PkbUtil::filterMap(getRelationshipManager(storage),getLeftArgEntities(storage));
    // Find intersection with all items of the right arg design entity
    auto res = PkbUtil::mapSetIntersection(filteredMap, getRightArgEntities(storage));
    setLeftArgResult(res.first);
    setRightArgResult(res.second);
}

void IntIntClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(leftArg.getValue(), PkbUtil::intSetToStringSet(result));
}

void IntIntClauseEvaluator::setRightArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(rightArg.getValue(), PkbUtil::intSetToStringSet(result));
}

std::unordered_set<int> IntIntClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> IntIntClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}
