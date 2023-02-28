#include "StringStringClauseEvaluator.h"

std::shared_ptr<ResultTable> StringStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateNumberNumber(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_STRING) {
        evaluateSynonymNumber(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_SYNONYM) {
        evaluateStringSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_WILDCARD) {
        evaluateStringWildCard(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_STRING) {
        evaluateStringString(storage);
    } else {
        throw std::exception();
    }
    optimiseResults();
    return clauseResultTable;
}

void StringStringClauseEvaluator::evaluateSynonymSynonym(StoragePointer storage) {
    auto relationshipStore = getRelationshipManager(storage);
    setLeftAndRightArgResult(relationshipStore);
}

void StringStringClauseEvaluator::evaluateStringSynonym(StoragePointer storage) {
    auto relationshipStore = getRelationshipManager(storage);
    if (relationshipStore.count(leftArg.getValue())) {
        setRightArgResult(relationshipStore.find(leftArg.getValue())->second);
    } else {
        clauseResultTable->setNoResults();
    }
}

void StringStringClauseEvaluator::evaluateStringWildCard(StoragePointer storage) {
    auto relationshipStore = getRelationshipManager(storage);
    if (!relationshipStore.count(leftArg.getValue())) {
        clauseResultTable->setNoResults();
    }
}

void StringStringClauseEvaluator::evaluateStringString(StoragePointer storage) {
    auto relationshipStore = getRelationshipManager(storage);
    auto iterator = relationshipStore.find(leftArg.getValue());
    if (iterator != relationshipStore.end() || !iterator->second.count(rightArg.getValue())) {
        clauseResultTable->setNoResults();
    }
}

void StringStringClauseEvaluator::handleLeftWildcard() {
    leftArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::PROCEDURE);
}

void StringStringClauseEvaluator::handleRightWildcard() {
    // Different for Calls/CallsT, need to override there
    rightArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::VARIABLE);
}

void StringStringClauseEvaluator::setLeftArgResult(std::unordered_set<std::string> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), result);
}

void StringStringClauseEvaluator::setRightArgResult(std::unordered_set<std::string> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
}

std::unordered_set<std::string> StringStringClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getStringEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<std::string> StringStringClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}\