#include "IntIntClauseEvaluator.h"

IntIntClauseEvaluator::IntIntClauseEvaluator(Argument left, Argument right, bool cacheable)
    : SuchThatClauseEvaluator<int, int>(left, right, cacheable) {}

void IntIntClauseEvaluator::evaluateEqualSynonym() {
    auto relationshipMap = cacheable ? getRelationshipCache(getLeftArgEntities()) : getRelationshipManager();
    if (isLeftArgAmbiguous()) {
        relationshipMap = Util::filterMap(relationshipMap, getLeftArgEntities());
    }
    setLeftArgResult(Util::getElementsWithCycles(relationshipMap));
}

void IntIntClauseEvaluator::setLeftArgResult(IntSet result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), Util::intSetToStringSet(result));
}

void IntIntClauseEvaluator::setRightArgResult(IntSet result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), Util::intSetToStringSet(result));
}

void IntIntClauseEvaluator::setLeftAndRightArgResult(IntIntMap results) {
    auto res = Util::intMapTostringMap(results);
    clauseResultTable = ResultTable::createTableFromMap(res, leftArg.getValue(), rightArg.getValue());
}

IntSet IntIntClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

IntSet IntIntClauseEvaluator::getRightArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

int IntIntClauseEvaluator::getLeftArg() {
    return stoi(leftArg.getValue());
}

int IntIntClauseEvaluator::getRightArg() {
    return stoi(rightArg.getValue());
}

bool IntIntClauseEvaluator::isLeftArgAmbiguous() {
    return leftArg.getDesignEntity() != DesignEntity::STMT;
}

bool IntIntClauseEvaluator::isRightArgAmbiguous() {
    return rightArg.getDesignEntity() != DesignEntity::STMT;
}
