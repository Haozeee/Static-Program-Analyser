#include "PatternClause.h"

#include <utility>

PatternClause::PatternClause(Argument patternArg, Argument left, StringExpression right)
        : patternArg(std::move(patternArg)), leftArg(std::move(left)), rightArg(std::move(right)) {}

Argument PatternClause::getPatternArg() {
    return patternArg;
}

Argument PatternClause::getLeftArg() {
    return leftArg;
}

StringExpression PatternClause::getRightArg() {
    return rightArg;
}
