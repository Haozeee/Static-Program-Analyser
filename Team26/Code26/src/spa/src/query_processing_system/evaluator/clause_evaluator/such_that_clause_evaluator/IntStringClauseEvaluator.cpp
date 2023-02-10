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
        default:
            throw std::exception();
    }
}

void IntStringClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(leftArg.getValue(), PkbUtil::intSetToStringSet(result));
}

void IntStringClauseEvaluator::setRightArgResult(std::unordered_set<std::string> result) {
    clauseResult->addNewResult(rightArg.getValue(), result);
}

std::unordered_set<int> IntStringClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<std::string> IntStringClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}
