#include "IfPatternClauseEvaluator.h"

#include <utility>
#include <unordered_set>
#include <unordered_map>

IfPatternClauseEvaluator::IfPatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

std::unordered_map<int, std::unordered_set<std::string>> IfPatternClauseEvaluator::getRelationshipEntries() {
    return storage->getIfCondManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<int>> IfPatternClauseEvaluator::getReverseRelationshipEntries() {
    return storage->getIfCondManager()->getAllReversedRelationshipEntries();
}
