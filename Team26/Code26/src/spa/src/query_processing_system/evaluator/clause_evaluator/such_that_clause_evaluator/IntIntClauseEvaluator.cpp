#include "IntIntClauseEvaluator.h"

IntIntClauseEvaluator::IntIntClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, int>(left, right) {}

std::shared_ptr<ClauseResult> IntIntClauseEvaluator::evaluateClause(StoragePointer storage) {
    switch (getClauseArgumentTypes()) {
        case ClauseArgumentTypes::NUMBER_NUMBER:
            evaluateNumberNumber(storage);
        case ClauseArgumentTypes::SYNONYM_NUMBER:
            evaluateSynonymNumber(storage);
        case ClauseArgumentTypes::NUMBER_SYNONYM:
            evaluateNumberSynonym(storage);
        case ClauseArgumentTypes::SYNONYM_SYNONYM:
            evaluateSynonymSynonym(storage);
        case ClauseArgumentTypes::NONE:
            throw std::exception();
    }
}
void IntIntClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(leftArg.getValue(), PkbUtil::intSetToStringSet(result));
}

void IntIntClauseEvaluator::setRightArgResult(std::unordered_set<int> result) {
    clauseResult->addNewResult(rightArg.getValue(), PkbUtil::intSetToStringSet(result));
}

std::unordered_set<int> IntIntClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> IntIntClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}
