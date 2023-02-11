#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

std::shared_ptr<ClauseResult> IntStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    switch (getClauseArgumentTypes()) {
        case ClauseArgumentTypes::NUMBER_SYNONYM:
            evaluateNumberSynonym(storage);
            break;
        case ClauseArgumentTypes::SYNONYM_SYNONYM:
            evaluateSynonymSynonym(storage);
            break;
        case ClauseArgumentTypes::SYNONYM_STRING:
            evaluateSynonymString(storage);
            break;
        case ClauseArgumentTypes::NUMBER_STRING:
            evaluateNumberString(storage);
            break;
        default:
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
