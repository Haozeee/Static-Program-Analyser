#include <utility>
#include "PatternClauseEvaluator.h"

PatternClauseEvaluator::PatternClauseEvaluator(Argument patternArg, Argument leftArg, StringExpression rightArg)
        : patternArg(std::move(patternArg)), leftArg(std::move(leftArg)), rightArg(std::move(rightArg)) {}

PatternClauseEvaluator::PatternClauseEvaluator(Argument patternArg, Argument leftArg)
        : patternArg(std::move(patternArg)), leftArg(std::move(leftArg)) {}

Argument PatternClauseEvaluator::getLeftArg() {
    return leftArg;
}

StringExpression PatternClauseEvaluator::getRightArg() {
    return rightArg;
}

std::shared_ptr<ResultTable> PatternClauseEvaluator::evaluateClause(ProgrammeStore storage_, CachePointer cache_) {
    setStorageLocation(storage_, cache_);
    auto leftArgType = leftArg.getArgumentType();
    if (leftArgType == ArgumentType::SYNONYM) {
        evaluateSynonym();
    } else if (leftArgType == ArgumentType::CHARACTERSTRING) {
        evaluateString();
    } else if (leftArgType == ArgumentType::WILDCARD) {
        evaluateWildcard();
    } else {
        // Not a valid pattern clause
        throw std::exception();
    }

    optimiseResults();
    return clauseResultTable;
}
