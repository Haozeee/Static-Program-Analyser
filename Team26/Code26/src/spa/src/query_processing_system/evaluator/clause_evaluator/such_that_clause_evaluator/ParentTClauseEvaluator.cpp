#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap ParentTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getParentTMap(interestedValues);
}

StmtStmtMap ParentTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getParentTReverseMap(interestedValues);
}

bool ParentTClauseEvaluator::isEmptyRelation() {
    return storage->isParentEmpty();
}
