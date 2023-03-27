#include "IfPatternClauseEvaluator.h"
#include <utility>

IfPatternClauseEvaluator::IfPatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

StmtEntityMap IfPatternClauseEvaluator::getRelationshipEntries() {
    return StorageUtil::getRelationshipMap(storage->getIfCondManager());
}

EntityStmtMap IfPatternClauseEvaluator::getReverseRelationshipEntries() {
    return StorageUtil::getReverseRelationshipMap(storage->getIfCondManager());
}
