#include "SuchThatClause.h"
#include <utility>

SuchThatClause::SuchThatClause(Argument left, Argument right)
    : leftArg(std::move(left)), rightArg(std::move(right)) {}

Argument SuchThatClause::getLeftArg() {
    return leftArg;
}

Argument SuchThatClause::getRightArg() {
    return rightArg;
}
