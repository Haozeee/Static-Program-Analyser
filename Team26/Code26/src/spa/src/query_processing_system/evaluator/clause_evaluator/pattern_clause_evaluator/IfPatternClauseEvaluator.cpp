#include "IfPatternClauseEvaluator.h"
#include <utility>

IfPatternClauseEvaluator::IfPatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

IntStringMap IfPatternClauseEvaluator::getRelationshipEntries() {
    return storage->getIfCondManager()->getAllRelationshipEntries();
}

StringIntMap IfPatternClauseEvaluator::getReverseRelationshipEntries() {
    return storage->getIfCondManager()->getAllReversedRelationshipEntries();
}
