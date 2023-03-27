#include "WhilePatternClauseEvaluator.h"
#include <utility>

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

StmtEntityMap WhilePatternClauseEvaluator::getRelationshipEntries() {
    return storage->getAllWhileCondEntries();
}

EntityStmtMap WhilePatternClauseEvaluator::getReverseRelationshipEntries() {
    return storage->getAllReverseWhileCondEntries();
}
