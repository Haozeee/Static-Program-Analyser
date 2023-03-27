#include "StringStringClauseEvaluator.h"

StringStringClauseEvaluator::StringStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<std::string, std::string>(left, right) {}

void StringStringClauseEvaluator::setLeftArgResult(EntitySet result) {
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM) {
        clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), result);
    }
}

void StringStringClauseEvaluator::setRightArgResult(EntitySet result) {
    if (rightArg.getArgumentType() == ArgumentType::SYNONYM) {
        clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
    }
}

void StringStringClauseEvaluator::setLeftAndRightArgResult(EntityEntityMap results) {
    if (leftArg.getArgumentType() == ArgumentType::SYNONYM && rightArg.getArgumentType() == ArgumentType::SYNONYM) {
        clauseResultTable = ResultTable::createTableFromMap(results, leftArg.getValue(), rightArg.getValue());
    }
}

EntitySet StringStringClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getStringEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

EntitySet StringStringClauseEvaluator::getRightArgEntities() {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

std::string StringStringClauseEvaluator::getLeftArg() {
    return leftArg.getValue();
}

std::string StringStringClauseEvaluator::getRightArg() {
    return rightArg.getValue();
}

bool StringStringClauseEvaluator::isLeftArgAmbiguous() {
    return false;
}

bool StringStringClauseEvaluator::isRightArgAmbiguous() {
    return false;
}
