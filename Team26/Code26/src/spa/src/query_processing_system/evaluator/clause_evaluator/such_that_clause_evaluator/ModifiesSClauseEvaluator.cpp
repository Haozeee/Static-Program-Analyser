#include "ModifiesSClauseEvaluator.h"

ModifiesSClauseEvaluator::ModifiesSClauseEvaluator(Argument left, Argument right)
        : IntStringClauseEvaluator(left, right) {}

StmtEntityMap ModifiesSClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getModifiesSMap(interestedValues);
}

EntityStmtMap ModifiesSClauseEvaluator::getOppositeRelationshipMap(EntitySet &interestedValues) {
    return storage->getModifiesSReverseMap(interestedValues);
}

bool ModifiesSClauseEvaluator::isEmptyRelation() {
    return storage->isModifiesSEmpty();
}
