#include "StringStringClauseEvaluator.h"

StringStringClauseEvaluator::StringStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<std::string, std::string>(left, right) {}

std::shared_ptr<ResultTable> StringStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_STRING) {
        evaluateSynonymValue(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_SYNONYM) {
        evaluateValueSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_WILDCARD) {
        evaluateValueWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::STRING_STRING) {
        evaluateValueValue(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_STRING) {
        evaluateWildcardValue(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_WILDCARD) {
        evaluateWildcardWildcard(storage);
    } else {
        throw std::exception();
    }
    optimiseResults();
    return clauseResultTable;
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

void StringStringClauseEvaluator::setLeftAndRightArgResult(std::unordered_map<std::string,
                                                           std::unordered_set<std::string>> results) {
    clauseResultTable = ResultTable::createTableFromMap(results, leftArg.getValue(), rightArg.getValue());
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
