#include "WhilePatternClauseEvaluator.h"
#include <utility>

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

StmtEntityMap WhilePatternClauseEvaluator::getRelationshipEntries() {
    return storage->getWhileCondManager()->getAllRelationshipEntries();
}

EntityStmtMap WhilePatternClauseEvaluator::getReverseRelationshipEntries() {
    return storage->getWhileCondManager()->getAllReversedRelationshipEntries();
}
