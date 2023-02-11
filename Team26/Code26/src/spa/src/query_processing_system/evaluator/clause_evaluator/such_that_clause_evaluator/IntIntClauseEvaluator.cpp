#include "IntIntClauseEvaluator.h"

IntIntClauseEvaluator::IntIntClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, int>(left, right) {}

std::shared_ptr<ClauseResult> IntIntClauseEvaluator::evaluateClause(StoragePointer storage) {
    ClauseArgumentTypes argumentType = getClauseArgumentTypes();
    switch (argumentType) {
        case ClauseArgumentTypes::NUMBER_NUMBER:
            evaluateNumberNumber(storage);
            break;
        case ClauseArgumentTypes::SYNONYM_NUMBER:
            evaluateSynonymNumber(storage);
            break;
        case ClauseArgumentTypes::NUMBER_SYNONYM:
            evaluateNumberSynonym(storage);
            break;
        case ClauseArgumentTypes::SYNONYM_SYNONYM:
            std::cout << "Synonym sybn\n";
            evaluateSynonymSynonym(storage);
            break;
        case ClauseArgumentTypes::NONE:
            std::cout << "None\n";
            throw std::exception();
    }
    return clauseResult;
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
