#include "ModifiesSClauseEvaluator.h"

ModifiesSClauseEvaluator::ModifiesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

StmtEntityMap ModifiesSClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getModifiesSManager());
}

EntityStmtMap ModifiesSClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getModifiesSManager());
}

bool ModifiesSClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getModifiesSManager());
}
