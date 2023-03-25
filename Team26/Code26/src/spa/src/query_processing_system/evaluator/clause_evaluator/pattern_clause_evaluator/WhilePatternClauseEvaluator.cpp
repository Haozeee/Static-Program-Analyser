#include "WhilePatternClauseEvaluator.h"

#include <utility>
#include <unordered_set>
#include <unordered_map>

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

IntStringMap WhilePatternClauseEvaluator::getRelationshipEntries() {
    return storage->getWhileCondManager()->getAllRelationshipEntries();
}

StringIntMap WhilePatternClauseEvaluator::getReverseRelationshipEntries() {
    return storage->getWhileCondManager()->getAllReversedRelationshipEntries();
}
