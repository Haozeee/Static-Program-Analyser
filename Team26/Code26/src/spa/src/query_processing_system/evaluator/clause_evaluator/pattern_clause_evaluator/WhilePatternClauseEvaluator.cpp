#include "WhilePatternClauseEvaluator.h"

#include <utility>
#include <unordered_set>
#include <unordered_map>

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

std::unordered_map<int, std::unordered_set<std::string>> WhilePatternClauseEvaluator::getRelationshipEntries() {
    return storage->getWhileCondManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<int>> WhilePatternClauseEvaluator::getReverseRelationshipEntries() {
    return storage->getWhileCondManager()->getAllReversedRelationshipEntries();
}
