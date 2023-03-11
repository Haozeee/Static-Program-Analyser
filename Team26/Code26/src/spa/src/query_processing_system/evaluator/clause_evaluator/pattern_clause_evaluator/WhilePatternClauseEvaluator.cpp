#include "WhilePatternClauseEvaluator.h"

#include <utility>

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : IfAndWhilePatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

std::unordered_map<int, std::unordered_set<std::string>>
WhilePatternClauseEvaluator::getRelationshipEntries(std::shared_ptr<ReadStorage> storage) {
    return storage->getWhileCondManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<int>>
WhilePatternClauseEvaluator::getReverseRelationshipEntries(std::shared_ptr<ReadStorage> storage) {
    return storage->getWhileCondManager()->getAllReversedRelationshipEntries();
}
