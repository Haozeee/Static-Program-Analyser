#include "PatternClause.h"

PatternClause::PatternClause(Argument left, std::variant<Wildcard, StringExpression> right)
        : leftArg(std::move(left)), rightArg(std::move(right)) {}

Argument PatternClause::getLeftArg() {
    return leftArg;
}

std::variant<Wildcard, StringExpression> PatternClause::getRightArg() {
    return rightArg;
}
