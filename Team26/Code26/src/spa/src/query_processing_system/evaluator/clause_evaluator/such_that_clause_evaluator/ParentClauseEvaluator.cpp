#include "ParentClauseEvaluator.h"

ParentClauseEvaluator::ParentClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap ParentClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getParentMap(interestedValues);
}

StmtStmtMap ParentClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getParentReverseMap(interestedValues);
}

bool ParentClauseEvaluator::isEmptyRelation() {
    return storage->isParentEmpty();
}
