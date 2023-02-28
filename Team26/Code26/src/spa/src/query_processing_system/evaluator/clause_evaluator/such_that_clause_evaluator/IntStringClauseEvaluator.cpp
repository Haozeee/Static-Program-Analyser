#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

std::shared_ptr<ResultTable> IntStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::NUMBER_STRING) {
        evaluateValueValue(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateValueSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_STRING) {
        evaluateSynonymString(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_WILDCARD) {
        evaluateValueWildcard(storage);
    } else {
        throw std::exception();
    }
    optimiseResults();
    return clauseResultTable;
}

void IntStringClauseEvaluator::evaluateSynonymString(StoragePointer storage) {
    std::unordered_set<int> leftResults;
    auto statementsToEvaluate = getLeftArgEntities(storage);
    for (int statement : statementsToEvaluate) {
        auto res = evaluateNumberSynonymHelper(storage, statement);
        if (res.count(rightArg.getValue())) {
            leftResults.insert(statement);
        }
    }
    setLeftArgResult(leftResults);
}

void IntStringClauseEvaluator::evaluateNumberString(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    if (!res.count(rightArg.getValue())) {
        clauseResultTable->setNoResults();
    }
}

void IntStringClauseEvaluator::evaluateNumberSynonym(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    setRightArgResult(res);
}

std::unordered_set<std::string> IntStringClauseEvaluator::evaluateNumberSynonymHelper(StoragePointer storage,
                                                                                      int stmtNumber) {
    auto relationshipStore = getRelationshipManager(storage);
    std::unordered_set<std::string> res;
    if (relationshipStore.count(stmtNumber)) {
        res = relationshipStore.find(stmtNumber)->second;
    }
    return res;
}

void IntStringClauseEvaluator::evaluateNumberWildcard(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    if (res.empty()) {
        clauseResultTable->setNoResults();
    }
}

void IntStringClauseEvaluator::handleLeftWildcard() {
    leftArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::STMT);
}

void IntStringClauseEvaluator::handleRightWildcard() {
    rightArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::VARIABLE);
}

void IntStringClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void IntStringClauseEvaluator::setRightArgResult(std::unordered_set<std::string> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
}

std::unordered_set<int> IntStringClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

void IntStringClauseEvaluator::setLeftAndRightArgResult(std::unordered_map<int,
                                                        std::unordered_set<std::string>> results) {
    auto res = PkbUtil::intStringMapTostringMap(results);
    clauseResultTable = ResultTable::createTableFromMap(res, leftArg.getValue(), rightArg.getValue());
}

std::unordered_set<std::string> IntStringClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

int IntStringClauseEvaluator::getLeftArg() {
    return stoi(leftArg.getValue());
}

std::string IntStringClauseEvaluator::getRightArg() {
    return rightArg.getValue();
}

bool IntStringClauseEvaluator::isLeftArgAmbiguous() {
    return true;
}

bool IntStringClauseEvaluator::isRightArgAmbiguous() {
    return false;
}
