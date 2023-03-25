#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

void IntStringClauseEvaluator::setLeftArgResult(IntSet result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), Util::intSetToStringSet(result));
}

void IntStringClauseEvaluator::setRightArgResult(StringSet result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
}

IntSet IntStringClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

StringSet IntStringClauseEvaluator::getRightArgEntities() {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

void IntStringClauseEvaluator::setLeftAndRightArgResult(IntStringMap results) {
    auto res = Util::intStringMapTostringMap(results);
    clauseResultTable = ResultTable::createTableFromMap(res, leftArg.getValue(), rightArg.getValue());
}

int IntStringClauseEvaluator::getLeftArg() {
    return stoi(leftArg.getValue());
}

std::string IntStringClauseEvaluator::getRightArg() {
    return rightArg.getValue();
}

bool IntStringClauseEvaluator::isLeftArgAmbiguous() {
    return leftArg.getDesignEntity() != DesignEntity::STMT;
}

bool IntStringClauseEvaluator::isRightArgAmbiguous() {
    return false;
}
