#include "IfPatternClauseEvaluator.h"

#include <utility>

IfPatternClauseEvaluator::IfPatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : IfAndWhilePatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

std::unordered_map<int, std::unordered_set<std::string>>
IfPatternClauseEvaluator::getRelationshipEntries(std::shared_ptr<ReadStorage> storage) {
    return storage->getIfCondManager()->getAllRelationshipEntries();
}

std::unordered_map<std::string, std::unordered_set<int>>
IfPatternClauseEvaluator::getReverseRelationshipEntries(std::shared_ptr<ReadStorage> storage) {
    return storage->getIfCondManager()->getAllReversedRelationshipEntries();
}
