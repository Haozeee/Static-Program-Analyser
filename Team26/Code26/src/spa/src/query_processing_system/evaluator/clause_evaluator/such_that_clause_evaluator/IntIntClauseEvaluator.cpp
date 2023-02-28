#include "IntIntClauseEvaluator.h"

IntIntClauseEvaluator::IntIntClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, int>(left, right) {}

std::shared_ptr<ResultTable> IntIntClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::NUMBER_NUMBER) {
        evaluateValueValue(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_NUMBER) {
        evaluateSynonymValue(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateValueSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_SYNONYM) {
        evaluateWildcardSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_WILDCARD) {
        evaluateValueWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_NUMBER) {
        evaluateWildcardValue(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_WILDCARD) {
        evaluateWildcardWildcard(storage);
    } else {
        throw std::exception();
    }
    optimiseResults();
    return clauseResultTable;
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

void IntIntClauseEvaluator::setLeftAndRightArgResult(std::unordered_map<int, std::unordered_set<int>> results) {
    auto res = PkbUtil::intMapTostringMap(results);
    clauseResultTable = ResultTable::createTableFromMap(res, leftArg.getValue(), rightArg.getValue());
}

std::unordered_set<int> IntIntClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> IntIntClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

int IntIntClauseEvaluator::getLeftArg() {
    return stoi(leftArg.getValue());
}

int IntIntClauseEvaluator::getRightArg() {
    return stoi(rightArg.getValue());
}

bool IntIntClauseEvaluator::isLeftArgAmbiguous() {
    return true;
}

bool IntIntClauseEvaluator::isRightArgAmbiguous() {
    return true;
}
