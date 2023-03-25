#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

void IntStringClauseEvaluator::setLeftArgResult(StmtSet result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), Util::intSetToStringSet(result));
}

void IntStringClauseEvaluator::setRightArgResult(EntitySet result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
}

StmtSet IntStringClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

EntitySet IntStringClauseEvaluator::getRightArgEntities() {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

void IntStringClauseEvaluator::setLeftAndRightArgResult(StmtEntityMap results) {
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
