#include "WhilePatternClauseEvaluator.h"
#include <utility>

WhilePatternClauseEvaluator::WhilePatternClauseEvaluator(Argument patternArg, Argument leftArg)
    : ExpressionlessPatternClauseEvaluator(std::move(patternArg), std::move(leftArg)) {}

StmtEntityMap WhilePatternClauseEvaluator::getRelationshipEntries() {
    return StorageUtil::getRelationshipMap(storage->getWhileCondManager());
}

EntityStmtMap WhilePatternClauseEvaluator::getReverseRelationshipEntries() {
    return StorageUtil::getReverseRelationshipMap(storage->getWhileCondManager());
}
