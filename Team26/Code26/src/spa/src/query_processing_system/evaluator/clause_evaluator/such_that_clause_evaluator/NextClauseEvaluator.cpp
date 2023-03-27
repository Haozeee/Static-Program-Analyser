#include "NextClauseEvaluator.h"

NextClauseEvaluator::NextClauseEvaluator(Argument left, Argument right)
    : IntIntClauseEvaluator(left, right) {}

StmtStmtMap NextClauseEvaluator::getRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getRelationshipMap(storage->getNextManager());
}

StmtStmtMap NextClauseEvaluator::getOppositeRelationshipMap(StmtSet &interestedValues) {
    return StorageUtil::getReverseRelationshipMap(storage->getNextManager());
}

bool NextClauseEvaluator::isEmptyRelation() {
    return StorageUtil::isRelationEmpty(storage->getNextManager());
}
