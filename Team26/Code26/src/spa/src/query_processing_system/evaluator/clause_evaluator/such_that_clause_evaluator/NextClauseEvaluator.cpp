#include "NextClauseEvaluator.h"

NextClauseEvaluator::NextClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

StmtStmtMap NextClauseEvaluator::getRelationshipManager() {
    return storage->getNextManager()->getAllRelationshipEntries();
}

StmtStmtMap NextClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getNextManager()->getAllReversedRelationshipEntries();
}
