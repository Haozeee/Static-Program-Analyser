#include "StringStringClauseEvaluator.h"

StringStringClauseEvaluator::StringStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<std::string, std::string>(left, right) {}

void StringStringClauseEvaluator::handleLeftWildcard() {
    leftArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::PROCEDURE);
}

void StringStringClauseEvaluator::setLeftArgResult(std::unordered_set<std::string> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), result);
}

void StringStringClauseEvaluator::setRightArgResult(std::unordered_set<std::string> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
}

void StringStringClauseEvaluator::setLeftAndRightArgResult(std::unordered_map<std::string,
                                                           std::unordered_set<std::string>> results) {
    clauseResultTable = ResultTable::createTableFromMap(results, leftArg.getValue(), rightArg.getValue());
}

std::unordered_set<std::string> StringStringClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getStringEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<std::string> StringStringClauseEvaluator::getRightArgEntities() {
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
