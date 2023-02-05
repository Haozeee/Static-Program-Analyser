#include "SuchThatClauseEvaluator.h"

SuchThatClauseEvaluator::SuchThatClauseEvaluator(Argument left, Argument right)
    : leftArg(left), rightArg(right) {}

Argument SuchThatClauseEvaluator::getLeftArg() {
    return leftArg;
}

Argument SuchThatClauseEvaluator::getRightArg() {
    return rightArg;
}
