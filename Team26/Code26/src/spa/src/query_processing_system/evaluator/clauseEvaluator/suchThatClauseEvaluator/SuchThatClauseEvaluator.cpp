#include "SuchThatClauseEvaluator.h"

SuchThatClauseEvaluator::SuchThatClauseEvaluator(Argument left, Argument right)
    : leftArg(left), rightArg(right), clauseResult(std::make_shared<ClauseResult>()) {}

Argument SuchThatClauseEvaluator::getLeftArg() {
    return leftArg;
}

Argument SuchThatClauseEvaluator::getRightArg() {
    return rightArg;
}

ClauseArgumentTypes SuchThatClauseEvaluator::getClauseArgumentTypes() {
    auto l = leftArg.getArgumentType();
    auto r = rightArg.getArgumentType();
    if (l == ArgumentType::NUMBER && r == ArgumentType::NUMBER) {
        return ClauseArgumentTypes::NUMBER_NUMBER;
    } else if (l == ArgumentType::SYNONYM && r == ArgumentType::NUMBER) {
        return ClauseArgumentTypes::SYNONYM_NUMBER;
    } else if (l == ArgumentType::NUMBER && r == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::NUMBER_SYNONYM;
    } else if (l == ArgumentType::SYNONYM && r == ArgumentType::SYNONYM) {
        return ClauseArgumentTypes::SYNONYM_SYNONYM;
    } else {
        return ClauseArgumentTypes::NONE;
    }
}
