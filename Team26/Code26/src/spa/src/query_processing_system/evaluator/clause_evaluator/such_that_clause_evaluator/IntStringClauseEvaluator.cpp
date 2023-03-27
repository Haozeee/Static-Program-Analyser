#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

void IntStringClauseEvaluator::setLeftArgResult(StmtSet result) {
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM) {
        clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), Util::intSetToStringSet(result));
    }
}

void IntStringClauseEvaluator::setRightArgResult(EntitySet result) {
    if (rightArg.getArgumentType() == ArgumentType::SYNONYM) {
        clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
    }
}

void IntStringClauseEvaluator::setLeftAndRightArgResult(StmtEntityMap results) {
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM && rightArg.getArgumentType() == ArgumentType::SYNONYM) {
        auto res = Util::intStringMapTostringMap(results);
        clauseResultTable = ResultTable::createTableFromMap(res, leftArg.getValue(), rightArg.getValue());
    }
}

StmtSet IntStringClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

EntitySet IntStringClauseEvaluator::getRightArgEntities() {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
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
