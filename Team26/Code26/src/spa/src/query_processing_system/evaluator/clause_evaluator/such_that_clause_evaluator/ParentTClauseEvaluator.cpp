#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap ParentTClauseEvaluator::getRelationshipManager() {
    return storage->getParentTManager()->getAllRelationshipEntries();
}

StmtStmtMap ParentTClauseEvaluator::getOppositeRelationshipManager() {
    return storage->getParentTManager()->getAllReversedRelationshipEntries();
}
