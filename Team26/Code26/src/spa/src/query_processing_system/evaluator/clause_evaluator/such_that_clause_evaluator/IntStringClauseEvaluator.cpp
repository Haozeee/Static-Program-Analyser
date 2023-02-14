#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

std::shared_ptr<ResultTable> IntStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::NUMBER_STRING) {
        evaluateNumberString(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateNumberSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_STRING) {
        evaluateSynonymString(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_WILDCARD) {
        evaluateNumberWildcard(storage);
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

void IntStringClauseEvaluator::evaluateSynonymSynonym(StoragePointer storage) {
    // Set initial empty results
    std::unordered_set<int> leftResults;
    std::unordered_set<std::string> rightResults;
    auto statementsToEvaluate = getLeftArgEntities(storage);
    for (int statement : statementsToEvaluate) {
        auto res = evaluateNumberSynonymHelper(storage, statement);
        if (!res.empty()) {
            leftResults.insert(statement);
            rightResults.insert(res.begin(), res.end());
        }
    }
    setLeftAndRightArgResult(leftResults, rightResults);
}

std::unordered_set<std::string> IntStringClauseEvaluator::evaluateNumberSynonymHelper(StoragePointer storage,
                                                                                      int stmtNumber) {
    auto parentRelation = storage->getParentTManager()->getAllRelationshipEntries();
    auto iterator = parentRelation.find(stmtNumber);
    auto relationshipStore = getRelationshipManager(storage);
    std::unordered_set<std::string> res;
    if (iterator != parentRelation.end()) {
        // This statement has children
        for (auto child : iterator->second) {
            if (relationshipStore.count(child)) {
                PkbUtil::setUnion(res, relationshipStore.find(child)->second);
            }
        }
    } else {
        if (relationshipStore.count(stmtNumber)) {
            PkbUtil::setUnion(res, relationshipStore.find(stmtNumber)->second);
        }
    }
    return res;
}

void IntStringClauseEvaluator::evaluateNumberWildcard(StoragePointer storage) {
    auto relationStore = getRelationshipManager(storage);
    auto iterator = relationStore.find(stoi(leftArg.getValue()));
    if (iterator == relationStore.end() || iterator->second.empty()) {
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

void IntStringClauseEvaluator::setLeftAndRightArgResult(std::unordered_set<int> resultLeft,
                                                        std::unordered_set<std::string> resultRight) {
    clauseResultTable = ResultTable::createDoubleColumnTable(leftArg.getValue(),
                                                             PkbUtil::intSetToStringSet(resultLeft),
                                                             rightArg.getValue(), resultRight);
}

std::unordered_set<int> IntStringClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<std::string> IntStringClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}
