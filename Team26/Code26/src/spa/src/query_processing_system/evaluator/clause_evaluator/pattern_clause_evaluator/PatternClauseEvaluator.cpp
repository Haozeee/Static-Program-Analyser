#include <utility>

#include "PatternClauseEvaluator.h"

PatternClauseEvaluator::PatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg)
        : patternArg(std::move(patternArg)), leftArg(std::move(leftArg)), rightArg(std::move(rightArg)) {}

Argument PatternClauseEvaluator::getLeftArg() {
    return leftArg;
}

StringExpression PatternClauseEvaluator::getRightArg() {
    return rightArg;
}
