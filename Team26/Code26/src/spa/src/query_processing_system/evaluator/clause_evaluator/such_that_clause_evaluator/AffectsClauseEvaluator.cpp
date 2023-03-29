#include "AffectsClauseEvaluator.h"

AffectsClauseEvaluator::AffectsClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap AffectsClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getAffectsMap(interestedValues);
}

StmtStmtMap AffectsClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getAffectsReverseMap(interestedValues);
}

bool AffectsClauseEvaluator::isEmptyRelation() {
    return storage->isAffectsEmpty();
}
