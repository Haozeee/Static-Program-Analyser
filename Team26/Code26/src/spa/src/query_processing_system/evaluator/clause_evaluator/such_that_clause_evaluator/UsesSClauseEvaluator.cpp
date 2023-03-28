#include "UsesSClauseEvaluator.h"

UsesSClauseEvaluator::UsesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

StmtEntityMap UsesSClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getUsesSMap(interestedValues);
}

EntityStmtMap UsesSClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getUsesSReverseMap(interestedValues);
}

bool UsesSClauseEvaluator::isEmptyRelation() {
    return storage->isUsesSEmpty();
}
