#include "ParentClauseEvaluator.h"

ParentClauseEvaluator::ParentClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap ParentClauseEvaluator::getRelationshipManager() {
    return storage->getParentManager()->getAllRelationshipEntries();
}

StmtStmtMap ParentClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getParentManager()->getAllReversedRelationshipEntries();
}
