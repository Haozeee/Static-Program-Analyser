#include "ParentClauseEvaluator.h"

ParentClauseEvaluator::ParentClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap ParentClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getParentManager());
}

StmtStmtMap ParentClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getParentManager());
}

bool ParentClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getParentManager());
}
