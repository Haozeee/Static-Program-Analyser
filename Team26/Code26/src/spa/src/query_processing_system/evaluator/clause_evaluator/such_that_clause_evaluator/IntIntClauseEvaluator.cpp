#include "IntIntClauseEvaluator.h"

IntIntClauseEvaluator::IntIntClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, int>(left, right) {}

std::shared_ptr<ResultTable> IntIntClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::NUMBER_NUMBER) {
        evaluateNumberNumber(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_NUMBER) {
        evaluateSynonymNumber(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateNumberSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_SYNONYM) {
        evaluateWildcardSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_WILDCARD ||
                argumentType == ClauseArgumentTypes::WILDCARD_NUMBER) {
        evaluateNumberWithWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_WILDCARD) {
        evaluateWildcardWildcard(storage);
    } else {
        throw std::exception();
    }
    optimiseResults();
    return clauseResultTable;
}

void IntIntClauseEvaluator::evaluateNumberNumber(StoragePointer storage) {
    auto relationshipStore = getRelationshipManager(storage);
    auto iterator = relationshipStore.find(stoi(leftArg.getValue()));
    auto rightValue = stoi(rightArg.getValue());
    if (iterator == relationshipStore.end() || !iterator->second.count(rightValue)) {
        clauseResultTable->setNoResults();
    }
}

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

void IntIntClauseEvaluator::evaluateSynonymSynonym(StoragePointer storage) {
    // Maybe can make use of the opposite relationship map??
    auto filteredMap = PkbUtil::filterMap(getRelationshipManager(storage), getLeftArgEntities(storage));
    // Find intersection with all items of the right arg design entity
    auto res = PkbUtil::mapSetIntersection(filteredMap, getRightArgEntities(storage));
    setLeftAndRightArgResult(PkbUtil::intMapTostringMap(res));
}

void IntIntClauseEvaluator::evaluateNumberWithWildcard(StoragePointer storage) {
    handleWildcards();
    if (leftArg.getArgumentType() == ArgumentType::NUMBER) {
        evaluateNumberSynonym(storage);
    } else {
        evaluateSynonymNumber(storage);
    }
    if (clauseResultTable->getNumberOfRows() == 0) {
        clauseResultTable->setNoResults();
    }
}

void IntIntClauseEvaluator::evaluateWildcardWildcard(StoragePointer storage) {
    auto relationMap = getRelationshipManager(storage);
    if (relationMap.empty()) {
        clauseResultTable->setNoResults();
    }
}
void IntIntClauseEvaluator::evaluateWildcardSynonym(StoragePointer storage) {
    handleLeftWildcard();
    evaluateSynonymSynonym(storage);
    // Remove wildcard placeholder
    clauseResultTable = ResultTable::createSingleColumnTable(
            rightArg.getValue(), clauseResultTable->getColumnValues(rightArg.getValue()));
}

void IntIntClauseEvaluator::handleLeftWildcard() {
    leftArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::STMT);
}

void IntIntClauseEvaluator::handleRightWildcard() {
    rightArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::STMT);
}

void IntIntClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void IntIntClauseEvaluator::setRightArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void IntIntClauseEvaluator::setLeftAndRightArgResult(
        std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    clauseResultTable = ResultTable::createTableFromMap(results, leftArg.getValue(), rightArg.getValue());
}

std::unordered_set<int> IntIntClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> IntIntClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}
