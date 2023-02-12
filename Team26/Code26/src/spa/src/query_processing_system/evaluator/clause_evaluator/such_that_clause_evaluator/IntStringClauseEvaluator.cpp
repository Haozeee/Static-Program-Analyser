#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

std::shared_ptr<ClauseResult> IntStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    ClauseArgumentTypes argumentType = getClauseArgumentTypes();
    if (argumentType == ClauseArgumentTypes::NUMBER_STRING) {
        evaluateNumberString(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateNumberSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_STRING) {
        evaluateSynonymString(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD ||
               argumentType == ClauseArgumentTypes::WILDCARD_SYNONYM) {
        handleWildcards();
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_WILDCARD) {
        evaluateNumberWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_STRING) {
        evaluateWildcardString(storage);
    } else if (argumentType == ClauseArgumentTypes::WILDCARD_WILDCARD) {
        // No evaluation needed
    } else {
        throw std::exception();
    }
    return clauseResult;
}

void IntStringClauseEvaluator::evaluateSynonymString(StoragePointer storage) {
    auto statementsToEvaluate = getLeftArgEntities(storage);
    for (int statement : statementsToEvaluate) {
        auto res = evaluateNumberSynonymHelper(storage, statement);
        if (res.count(rightArg.getValue())) {
            setLeftArgResult({statement});
        } else {
            setLeftArgResult({});
        }
    }
}

void IntStringClauseEvaluator::evaluateNumberString(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    if (!res.count(rightArg.getValue())) {
        clauseResult->setNoResults();
    }
}

void IntStringClauseEvaluator::evaluateNumberSynonym(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    setRightArgResult(res);
}

void IntStringClauseEvaluator::evaluateSynonymSynonym(StoragePointer storage) {
    // Set initial empty results
    setRightArgResult({});
    setLeftArgResult({});
    auto statementsToEvaluate = getLeftArgEntities(storage);
    for (int statement : statementsToEvaluate) {
        auto res = evaluateNumberSynonymHelper(storage, statement);
        if (!res.empty()) {
            setRightArgResult(res);
            setLeftArgResult({statement});
        }
    }
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
        clauseResult->setNoResults();
    }
}

void IntStringClauseEvaluator::evaluateWildcardString(StoragePointer storage) {
    auto relationStore = getOppositeRelationshipManager(storage);
    auto iterator = relationStore.find(rightArg.getValue());
    if (iterator == relationStore.end() || iterator->second.empty()) {
        clauseResult->setNoResults();
    }
}

void IntStringClauseEvaluator::handleLeftWildcard() {
    leftArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::STMT);
}

void IntStringClauseEvaluator::handleRightWildcard() {
    rightArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::VARIABLE);
}

void IntStringClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResult->unionResult(leftArg.getValue(), PkbUtil::intSetToStringSet(result));
}

void IntStringClauseEvaluator::setRightArgResult(std::unordered_set<std::string> result) {
    clauseResult->unionResult(rightArg.getValue(), result);
}

std::unordered_set<int> IntStringClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<std::string> IntStringClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}
