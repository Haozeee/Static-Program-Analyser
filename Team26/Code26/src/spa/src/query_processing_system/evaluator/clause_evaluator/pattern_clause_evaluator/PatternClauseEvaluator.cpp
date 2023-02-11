#include <utility>

#include "PatternClauseEvaluator.h"

PatternClauseEvaluator::PatternClauseEvaluator(DesignEntity designEntity, Argument leftArg, StringExpression rightArg)
        : designEntity(designEntity), leftArg(std::move(leftArg)), rightArg(std::move(rightArg)), clauseResult(std::make_shared<ClauseResult>()) {}

DesignEntity PatternClauseEvaluator::getDesignEntity() {
    return designEntity;
}
Argument PatternClauseEvaluator::getLeftArg() {
    return leftArg;
}

StringExpression PatternClauseEvaluator::getRightArg() {
    return rightArg;
}
