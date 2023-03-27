#include "UsesSClauseEvaluator.h"

UsesSClauseEvaluator::UsesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

StmtEntityMap UsesSClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getUsesSManager());
}

EntityStmtMap UsesSClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getUsesSManager());
}

bool UsesSClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getUsesSManager());
}
