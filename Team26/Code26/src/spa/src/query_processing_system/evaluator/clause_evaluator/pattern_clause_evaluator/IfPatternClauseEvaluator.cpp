#include "IfPatternClauseEvaluator.h"
#include <utility>

IfPatternClauseEvaluator::IfPatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

StmtEntityMap IfPatternClauseEvaluator::getRelationshipEntries() {
    return storage->getIfCondManager()->getAllRelationshipEntries();
}

EntityStmtMap IfPatternClauseEvaluator::getReverseRelationshipEntries() {
    return storage->getIfCondManager()->getAllReversedRelationshipEntries();
}
