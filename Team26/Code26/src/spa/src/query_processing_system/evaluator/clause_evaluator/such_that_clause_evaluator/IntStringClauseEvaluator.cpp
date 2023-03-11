#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

void IntStringClauseEvaluator::handleLeftWildcard() {
    leftArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::STMT);
}

void IntStringClauseEvaluator::handleRightWildcard() {
    rightArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::VARIABLE);
}

void IntStringClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(), Util::intSetToStringSet(result));
}

void IntStringClauseEvaluator::setRightArgResult(std::unordered_set<std::string> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
}

std::unordered_set<int> IntStringClauseEvaluator::getLeftArgEntities() {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<std::string> IntStringClauseEvaluator::getRightArgEntities() {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

void IntStringClauseEvaluator::setLeftAndRightArgResult(std::unordered_map<int,
                                                        std::unordered_set<std::string>> results) {
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
    return true;
}

bool IntStringClauseEvaluator::isRightArgAmbiguous() {
    return false;
}
