#include "PatternClauseEvaluator.h"

PatternClauseEvaluator::PatternClauseEvaluator(Argument leftArg, std::variant<Wildcard, StringExpression> rightArg)
        : leftArg(std::move(leftArg)), rightArg(std::move(rightArg)), clauseResult(std::make_shared<ClauseResult>()) {}

Argument PatternClauseEvaluator::getLeftArg() {
    return leftArg;
}

std::variant<Wildcard, StringExpression> PatternClauseEvaluator::getRightArg() {
    return rightArg;
}
