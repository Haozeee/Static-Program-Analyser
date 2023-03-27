#include "AffectsTClauseEvaluator.h"

AffectsTClauseEvaluator::AffectsTClauseEvaluator(Argument left, Argument right) : IntIntClauseEvaluator(left, right) {}

StmtStmtMap AffectsTClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return storage->getAffectsTMap(interestedValues);
}

StmtStmtMap AffectsTClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return storage->getAffectsTReverseMap(interestedValues);
}

bool AffectsTClauseEvaluator::isEmptyRelation() {
    return storage->isAffectsEmpty();
}
