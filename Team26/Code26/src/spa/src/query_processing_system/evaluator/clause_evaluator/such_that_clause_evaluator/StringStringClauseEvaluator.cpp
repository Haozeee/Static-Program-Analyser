#include "StringStringClauseEvaluator.h"

StringStringClauseEvaluator::StringStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<std::string, std::string>(left, right) {}

std::shared_ptr<ResultTable> StringStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_SYNONYM) {
        evaluateStringSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_WILDCARD) {
        evaluateValueWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_STRING) {
        evaluateValueValue(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_STRING) {
        evaluateWildcardValue(storage);
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
}

std::string StringStringClauseEvaluator::getLeftArg() {
    return leftArg.getValue();
}

std::string StringStringClauseEvaluator::getRightArg() {
    return rightArg.getValue();
}

bool StringStringClauseEvaluator::isLeftArgAmbiguous() {
    return false;
}

bool StringStringClauseEvaluator::isRightArgAmbiguous() {
    return false;
}
