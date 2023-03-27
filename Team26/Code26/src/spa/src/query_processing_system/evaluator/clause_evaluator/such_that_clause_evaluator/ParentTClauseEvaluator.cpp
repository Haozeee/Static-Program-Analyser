#include "ParentTClauseEvaluator.h"

ParentTClauseEvaluator::ParentTClauseEvaluator(Argument left, Argument right)
        : IntIntClauseEvaluator(left, right) {}

StmtStmtMap ParentTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getParentTManager());
}

StmtStmtMap ParentTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getParentTManager());
}

bool ParentTClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getParentTManager());
}
